/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz <molasz.dev@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 23:08:48 by molasz            #+#    #+#             */
/*   Updated: 2026/04/01 20:46:32 by molasz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

void	*malloc(size_t size)
{
	t_zone	*zone;
	t_block	*block;

	zone = find_or_create_zone(size);
	if (!zone)
		return (NULL);
	block = find_block(zone, size);
	if (!block)
		return (NULL);
	return (block + 1);
}
