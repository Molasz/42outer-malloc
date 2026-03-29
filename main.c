/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz <molasz.dev@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 01:31:41 by molasz            #+#    #+#             */
/*   Updated: 2026/03/29 03:16:53 by molasz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include <stdio.h>

int	main(void)
{
	printf("sizeof(t_zone): %ld sizeof(t_block)%ld\n",
		sizeof(t_zone), sizeof(t_block));
	printf("PAGE_SIZE: %d\n", PAGE_SIZE);
	printf("TINY: %d SMALL: %d\n", TINY_ZONE, SMALL_ZONE);
	printf("TINY_BLOCK: %d (%d)\n", TINY_BLOCK,
		(TINY_BLOCK + BLOCK_SIZE) * 100 + ZONE_SIZE);
	printf("SMALL_BLOCK: %d (%d)\n", SMALL_BLOCK,
		(SMALL_BLOCK + BLOCK_SIZE) * 100 + ZONE_SIZE);
	return (0);
}
