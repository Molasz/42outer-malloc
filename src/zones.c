/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zones.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz <molasz.dev@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 00:02:28 by molasz            #+#    #+#             */
/*   Updated: 2026/03/29 01:56:59 by molasz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

t_zone	*g_zones[3];

t_zone_type	get_type(size_t size)
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

	ptr = mmap(NULL, size, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (ptr == MAP_FAILED)
		return (NULL);
	return (ptr);
}

t_zone	*create_zone(size_t size, t_zone_type type)
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
	t_zone		*zone;
	t_zone_type	type;

	type = get_type(size);
	if (type == LARGE)
		return (create_zone(size, type));
	zone = g_zones[type];
	if (!zone)
		return (create_zone(size, type));
	while (zone)
	{
		if (zone->total - zone->used >= BLOCK_SIZE + size)
			return (zone);
		zone = zone->next;
	}
	return (create_zone(size, type));
}
