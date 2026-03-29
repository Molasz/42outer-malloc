/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz <molasz.dev@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 01:31:41 by molasz            #+#    #+#             */
/*   Updated: 2026/03/29 01:59:46 by molasz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include <stdio.h>

int	main(void)
{
	printf("PAGE_SIZE: %ld\n", PAGE_SIZE);
	printf("TINY: %ld SMALL: %ld\n", TINY_ZONE, SMALL_ZONE);
	printf("TINY_BLOCK: %d (%ld)\n", TINY_BLOCK,
		(TINY_BLOCK + BLOCK_SIZE) * 100 + ZONE_SIZE);
	printf("SMALL_BLOCK: %d (%ld)\n", SMALL_BLOCK,
		(SMALL_BLOCK + BLOCK_SIZE) * 100 + ZONE_SIZE);
	return (0);
}
