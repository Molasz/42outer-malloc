/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz <molasz.dev@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 23:08:48 by molasz            #+#    #+#             */
/*   Updated: 2026/04/02 04:23:04 by molasz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

void	*malloc(size_t size)
{
	t_zone	*zone;
	t_block	*block;
	size_t	align_size;

	if (!size)
		return (NULL);
	align_size = align16(size);
	zone = find_zone(align_size);
	if (!zone)
		return (NULL);
	block = find_block(zone, size);
	if (!block)
		return (NULL);
	return (block + 1);
}
