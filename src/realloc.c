/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz <molasz.dev@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 23:10:57 by molasz            #+#    #+#             */
/*   Updated: 2026/04/03 03:00:54 by molasz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

static t_block	*validate_blocks(void *ptr, t_block *block)
{
	while (block)
	{
		if ((char *)block + BLOCK_SIZE == ptr)
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

static void	*call_malloc_realloc(void *old, t_block *block, size_t size)
{
	size_t	alsize;
	size_t	alblock;
	void	*ptr;

	alsize = align_size(size, 16);
	alblock = align_size(block->size, 16);
	if (alsize <= alblock)
	{
		if (alblock >= alsize + BLOCK_SIZE + 16)
			fractionate_block(block, size, alsize);
		else
			block->size = size;
		return (old);
	}
	ptr = call_malloc(size);
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, old, block->size);
	call_free(old);
	return (ptr);
}

void	*realloc(void *ptr, size_t size)
{
	t_block	*block;
	void	*new;

	if (!ptr)
		return (malloc(size));
	if (!size)
	{
		free(ptr);
		return (NULL);
	}
	pthread_mutex_lock(&g_malloc_mutex);
	block = validate_zones(ptr);
	if (!block)
	{
		pthread_mutex_unlock(&g_malloc_mutex);
		return (NULL);
	}
	new = call_malloc_realloc(ptr, block, size);
	pthread_mutex_unlock(&g_malloc_mutex);
	return (new);
}
