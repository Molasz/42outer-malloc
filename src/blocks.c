/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz <molasz.dev@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 01:06:29 by molasz            #+#    #+#             */
/*   Updated: 2026/03/30 02:18:50 by molasz           ###   ########.fr       */
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
	return (block);
}

t_block	*find_block(t_zone *zone, size_t size)
{
	t_block	*block;

	if (!zone->blocks)
		return (create_block(zone, NULL, size));
	block = zone->blocks;
	while (block->next)
	{
		if (block->free && block->size >= size)
		{
			block->free = 0;
			return (block);
		}
		block = block->next;
	}
	return (create_block(zone, block ,size));
}
