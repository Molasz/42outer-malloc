/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zones.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz <molasz.dev@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 00:02:28 by molasz            #+#    #+#             */
/*   Updated: 2026/04/02 00:01:20 by molasz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

t_zone	*g_zones[3];

static void	*call_mmap(size_t size)
{
	void	*ptr;

	ptr = mmap(NULL, size, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (ptr == MAP_FAILED)
		return (NULL);
	return (ptr);
}

static t_zone	*create_zone(size_t size, t_zone_type type)
{
	size_t	zone_size;
	t_zone	*zone;

	if (type == TINY)
		zone_size = TINY_ZONE;
	else if (type == SMALL)
		zone_size = SMALL_ZONE;
	else
		zone_size = BLOCK_SIZE + size;
	zone = call_mmap(zone_size + ZONE_SIZE);
	if (zone)
	{
		zone->total = zone_size;
		zone->used = 0;
		zone->next = NULL;
		zone->blocks = NULL;
	}
	return (zone);
}

t_zone	*find_or_create_zone(size_t size)
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
