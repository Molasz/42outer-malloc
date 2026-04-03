/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_calls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz <molasz.dev@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 01:49:36 by molasz            #+#    #+#             */
/*   Updated: 2026/04/03 02:21:22 by molasz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

t_zone			*g_zones[3];
pthread_mutex_t	g_malloc_mutex = PTHREAD_MUTEX_INITIALIZER;

void	*call_mmap(size_t size)
{
	void	*ptr;

	ptr = mmap(NULL, size,
			PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (ptr == MAP_FAILED)
		return (NULL);
	return (ptr);
}

void	call_munmap(t_zone *zone, t_zone *prev, t_zone_type type)
{
	if (!prev)
		g_zones[type] = zone->next;
	else
		prev->next = zone->next;
	munmap(zone, zone->total + ZONE_SIZE);
}
