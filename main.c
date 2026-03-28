/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz <molasz.dev@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 01:31:41 by molasz            #+#    #+#             */
/*   Updated: 2026/03/28 02:04:21 by molasz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include <stdio.h>

void	main()
{
	printf("PAGE_SIZE: %ld\nTINY: %ld\nSMALL: %ld\nTINY_BLOCK: %d (%ld)\nSMALL_BLOCK: %d (%ld)\n", PAGE_SIZE, TINY_ZONE, SMALL_ZONE, TINY_BLOCK, (TINY_BLOCK + BLOCK_SIZE) * 100 + AREA_SIZE, SMALL_BLOCK, (SMALL_BLOCK + BLOCK_SIZE) * 100 + AREA_SIZE);
}
