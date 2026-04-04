/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz <molasz.dev@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 23:08:48 by molasz            #+#    #+#             */
/*   Updated: 2026/04/04 20:48:13 by molasz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

void	*call_malloc(size_t size)
{
	t_zone	*zone;
	t_block	*block;
	size_t	alsize;

	if (!size)
		return (NULL);
	alsize = align_size(size, 16);
	zone = find_zone(alsize);
	if (!zone)
		return (NULL);
	block = find_block(zone, size, alsize);
	if (!block)
		return (NULL);
	return ((char *)block + BLOCK_SIZE);
}

void	*malloc(size_t size)
{
	void	*ptr;

	pthread_mutex_lock(&g_malloc_mutex);
	ptr = call_malloc(size);
	pthread_mutex_unlock(&g_malloc_mutex);
	return (ptr);
}

