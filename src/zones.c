/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zones.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz <molasz.dev@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 00:02:28 by molasz            #+#    #+#             */
/*   Updated: 2026/04/03 00:58:34 by molasz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

t_zone	*g_zones[3];

static t_zone_type	get_type(size_t size)
{
	t_zone_type	z;

	if (size <= TINY_BLOCK)
		z = TINY;
	else if (size <= SMALL_BLOCK)
		z = SMALL;
	else
		z = LARGE;
	return (z);
}

static void	*call_mmap(size_t size)
{
	void	*ptr;

	ptr = mmap(NULL, size,
			PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (ptr == MAP_FAILED)
		return (NULL);
	return (ptr);
}

static size_t	get_zone_size(t_zone_type type, size_t pagesize)
{
	size_t	size;

	if (type == TINY)
		size = TINY_BLOCK;
	else if (type == SMALL)
		size = SMALL_BLOCK;
	return (align_size(100 * (size + BLOCK_SIZE) + ZONE_SIZE, pagesize));
}

static t_zone	*create_zone(size_t size, t_zone_type type)
{
	size_t	zone_size;
	size_t	page_size;
	t_zone	*zone;

	page_size = sysconf(_SC_PAGESIZE);
	if (type != LARGE)
		zone_size = get_zone_size(type, page_size);
	else
		zone_size = align_size(size + BLOCK_SIZE + ZONE_SIZE, page_size);
	zone = call_mmap(zone_size + ZONE_SIZE);
	if (zone)
	{
		zone->total = zone_size - ZONE_SIZE;
		zone->used = 0;
		zone->next = NULL;
		zone->blocks = NULL;
	}
	return (zone);
}

t_zone	*find_zone(size_t size)
{
	t_zone_type	type;
	t_zone		*zone;
	t_zone		*prev;

	prev = NULL;
	type = get_type(size);
	zone = g_zones[type];
	if (!zone)
	{
		g_zones[type] = create_zone(size, type);
		return (g_zones[type]);
	}
	while (zone)
	{
		if (zone->total - zone->used >= BLOCK_SIZE + size && type != LARGE)
			return (zone);
		prev = zone;
		zone = zone->next;
	}
	prev->next = create_zone(size, type);
	return (prev->next);
}
