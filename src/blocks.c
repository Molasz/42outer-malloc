/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz <molasz.dev@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 01:06:29 by molasz            #+#    #+#             */
/*   Updated: 2026/04/01 20:41:42 by molasz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

static t_block	*create_block(t_zone *zone, t_block *prev, size_t size)
{
	t_block	*block;

	if (prev)
		block = (t_block *)((char *)prev + BLOCK_SIZE + prev->size);
	else
		block = (t_block *)((char *)zone + ZONE_SIZE);
	block->size = size;
	block->free = 0;
	block->next = NULL;
	block->prev = prev;
	if (prev)
		prev->next = block;
	else
		zone->blocks = block;
	zone->used += size;
	return (block);
}

t_block	*find_block(t_zone *zone, size_t size)
{
	t_block	*block;
	t_block	*prev;

	if (!zone->blocks)
		return (create_block(zone, NULL, size));
	block = zone->blocks;
	while (block)
	{
		if (block->free && block->size >= size)
		{
			block->free = 0;
			return (block);
		}
		prev = block;
		block = block->next;
	}
	return (create_block(zone, prev, size));
}
