/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz <molasz.dev@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 01:06:29 by molasz            #+#    #+#             */
/*   Updated: 2026/04/03 02:34:19 by molasz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

void	coalesce_blocks(t_zone *zone)
{
	t_block	*block;

	block = zone->blocks;
	while (block && block->next)
	{
		if (block->free && block->next->free)
		{
			block->size += align_size(block->next->size, 16) + BLOCK_SIZE;
			block->next = block->next->next;
		}
		else
			block = block->next;
	}
}

static t_block	*create_block(t_zone *zone, t_block *prev,
	size_t size, size_t alsize)
{
	t_block	*block;

	if (prev)
		block = (t_block *)((char *)prev
				+ BLOCK_SIZE + align_size(prev->size, 16));
	else
		block = (t_block *)((char *)zone + ZONE_SIZE);
	block->size = size;
	block->free = 0;
	block->next = NULL;
	if (prev)
		prev->next = block;
	else
		zone->blocks = block;
	zone->used += alsize + BLOCK_SIZE;
	return (block);
}

void	fractionate_block(t_block *old, size_t size, size_t alsize)
{
	t_block	*block;

	block = (t_block *)((char *)(old + BLOCK_SIZE) + alsize);
	block->size = align_size(old->size, 16) - alsize - BLOCK_SIZE;
	block->free = 1;
	block->next = old->next;
	old->next = block;
	old->size = size;
}

t_block	*find_block(t_zone *zone, size_t size, size_t alsize)
{
	t_block	*block;
	t_block	*prev;
	size_t	alblock;

	if (!zone->blocks)
		return (create_block(zone, NULL, size, alsize));
	block = zone->blocks;
	while (block)
	{
		alblock = align_size(block->size, 16);
		if (block->free && alblock >= size)
		{
			if (alblock >= alsize + BLOCK_SIZE + 16)
				fractionate_block(block, size, alsize);
			else
				block->size = size;
			block->free = 0;
			return (block);
		}
		prev = block;
		block = block->next;
	}
	return (create_block(zone, prev, size, alsize));
}
