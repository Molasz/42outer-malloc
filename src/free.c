/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz <molasz.dev@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 23:07:47 by molasz            #+#    #+#             */
/*   Updated: 2026/04/03 00:56:00 by molasz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

static void	call_munmap(t_zone *zone, t_zone *prev, t_zone_type t)
{
	if (!prev)
		g_zones[t] = zone->next;
	else
		prev->next = zone->next;
	munmap(zone, zone->total + ZONE_SIZE);
}

static void	validate_zone(t_zone *zone, t_zone *prev, t_zone_type t)
{
	t_block	*block;

	block = zone->blocks;
	while (block)
	{
		if (!block->free)
			return ;
		block = block->next;
	}
	call_munmap(zone, prev, t);
}

static void	check_blocks(char *ptr, t_zone *zone, t_zone *prev, t_zone_type t)
{
	t_block	*block;

	block = zone->blocks;
	while (block)
	{
		if (ptr == (char *)(block + 1))
		{
			if (!block->free)
			{
				block->free = 1;
				zone->used -= align_size(block->size, 16);
				if (t == LARGE)
					call_munmap(zone, prev, t);
				else if (((t_zone *)g_zones[t])->next)
					validate_zone(zone, prev, t);
			}
			return ;
		}
		block = block->next;
	}
}

static void	check_zones(char *ptr)
{
	int		type;
	t_zone	*zone;
	t_zone	*prev;

	type = 0;
	while (type < 3)
	{
		prev = NULL;
		zone = g_zones[type];
		while (zone)
		{
			if (ptr > (char *)zone
				&& ptr < (char *)zone + ZONE_SIZE + zone->total)
			{
				check_blocks(ptr, zone, prev, type);
				return ;
			}
			prev = zone;
			zone = zone->next;
		}
		type++;
	}
}

void	free(void *ptr)
{
	if (!ptr)
		return ;
	check_zones(ptr);
}
