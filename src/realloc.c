/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz <molasz.dev@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 23:10:57 by molasz            #+#    #+#             */
/*   Updated: 2026/04/02 04:27:51 by molasz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

static t_block	*validate_blocks(void *ptr, t_block *block)
{
	while (block)
	{
		if ((void *)(block + 1) == ptr)
			return (block);
		block = block->next;
	}
	return (NULL);
}

static t_block	*validate_zones(void *ptr)
{
	int		type;
	t_zone	*zone;
	t_block	*block;

	type = 0;
	while (type < 3)
	{
		zone = g_zones[type];
		while (zone)
		{
			if ((char *)ptr > (char *)zone
				&& (char *)ptr < (char *)zone + ZONE_SIZE + zone->total)
			{
				block = validate_blocks(ptr, zone->blocks);
				if (block)
					return (block); 
			}
			zone = zone->next;
		}
		type++;
	}
	return (NULL);
}

static void	*call_malloc(void *old, t_block *block, size_t size)
{
	size_t	aligned_size;
	void	*ptr;

	aligned_size = align16(size);
	if (aligned_size <= block->size)
	{
		if (block->size >= aligned_size + BLOCK_SIZE + 16)
			fractionate_block(block, aligned_size);
		else
			block->size = size;
		return (old);
	}
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, old, block->size);
	free(old);
	return (ptr);
}

void	*realloc(void *ptr, size_t size)
{
	t_block	*block;
	void	*new;

	if (!ptr)
		return (malloc(size));
	if (!size)
		return (free(ptr), NULL);
	block = validate_zones(ptr);
	if (!block)
		return (NULL);
	new = call_malloc(ptr, block, size);
	return (new);
}
