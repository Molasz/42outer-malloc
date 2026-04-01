/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz <molasz.dev@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 01:06:29 by molasz            #+#    #+#             */
/*   Updated: 2026/04/02 00:56:27 by molasz           ###   ########.fr       */
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
	zone->used += size + BLOCK_SIZE;
	return (block);
}

static void	fractionate_block(t_block *old, size_t size)
{
	t_block	*block;

	block = (t_block *)((char *)(old + 1) + size);
	block->size = old->size - size - BLOCK_SIZE;
	block->free = 1;
	block->next = old->next;
	block->prev = old;
	if (old->next)
		old->next->prev = block;
	old->next = block;
	old->size = size;
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
			if (block->size >= size + BLOCK_SIZE + 16)
				fractionate_block(block, size);
			block->free = 0;
			return (block);
		}
		prev = block;
		block = block->next;
	}
	return (create_block(zone, prev, size));
}
