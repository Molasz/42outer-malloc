/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz <molasz.dev@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 23:10:24 by molasz            #+#    #+#             */
/*   Updated: 2026/04/02 00:21:52 by molasz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

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

size_t	align16(size_t size)
{
	return ((size + 15) & ~15);
}
