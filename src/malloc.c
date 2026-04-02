/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz <molasz.dev@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 23:08:48 by molasz            #+#    #+#             */
/*   Updated: 2026/04/03 00:25:33 by molasz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

void	*malloc(size_t size)
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
	return (block + 1);
}
