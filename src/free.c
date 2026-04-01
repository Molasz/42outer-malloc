/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz <molasz.dev@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 23:07:47 by molasz            #+#    #+#             */
/*   Updated: 2026/04/01 20:28:04 by molasz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

static t_zone	*find_zone(t_block *block)
{
	while (block->prev)
		block = block->prev;
	return (t_zone *)((char *)block - BLOCK_SIZE - ZONE_SIZE);
}

static void	call_munmap(t_zone *zone, t_zone_type type)
{
	t_zone	*prev;

	prev = g_zones[type];
	if (prev == zone && !prev->next)
		return;
	while (prev->next == zone)
		prev = prev->next;
	prev->next = zone->next;
	munmap(zone, zone->total + ZONE_SIZE + BLOCK_SIZE);
}

static void	validate_zone(t_zone *zone, t_zone_type type)
{
	t_block	*block;

	if (zone->used * 10 < zone->total * 9)
		return;
	while (block)
	{
		if (!block->free)
			return;
		block = block->next;
	}
	call_munmap(zone, type);
}

void	free(void *ptr)
{
	t_zone		*zone;
	t_block		*block;
	t_zone_type	type;

	if (!ptr)
		return;
	block = (t_block *) ptr - 1;
	block->free = 1;
	zone = find_zone(block);
	type = get_type(zone->total);
	if (type == LARGE)
		call_munmap(zone, type);
	else
		validate_zone(zone, type);
}
