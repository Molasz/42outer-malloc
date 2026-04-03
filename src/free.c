/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz <molasz.dev@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 23:07:47 by molasz            #+#    #+#             */
/*   Updated: 2026/04/03 03:00:48 by molasz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

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
		if (ptr == (char *)block + BLOCK_SIZE)
		{
			if (!block->free)
			{
				block->free = 1;
				coalesce_blocks(zone);
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

void	call_free(void *ptr)
{
	if (!ptr)
		return ;
	check_zones(ptr);
}

void	free(void *ptr)
{
	pthread_mutex_lock(&g_malloc_mutex);
	call_free(ptr);
	pthread_mutex_unlock(&g_malloc_mutex);
}
