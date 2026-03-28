/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz <molasz.dev@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 23:08:48 by molasz            #+#    #+#             */
/*   Updated: 2026/03/28 02:07:52 by molasz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

void	*malloc(size_t size)
{
	void	*ptr;

	ptr = NULL;

	if (size <= TINY_BLOCK)
	{}
	else if (size <= SMALL_BLOCK)
	{}
	else
	{}

	return (ptr);
}
