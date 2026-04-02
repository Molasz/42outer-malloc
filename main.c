/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz <molasz.dev@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 01:31:41 by molasz            #+#    #+#             */
/*   Updated: 2026/04/02 04:31:07 by molasz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include <stdio.h>

void    print_sizes(void)
{
    printf("\n--- SIZE ---\n");
	printf("ALIGN(sizeof(t_zone)): %ld\n", align16(sizeof(t_zone)));
	printf("ALIGN(sizeof(t_block)): %ld\n", align16(sizeof(t_block)));
	printf("PAGE_SIZE: %d\n", PAGE_SIZE);
	printf("TINY: %d SMALL: %d\n", TINY_ZONE, SMALL_ZONE);
	printf("TINY_BLOCK: %d (%d)\n", TINY_BLOCK,
		(TINY_BLOCK + BLOCK_SIZE) * 100 + ZONE_SIZE);
	printf("SMALL_BLOCK: %d (%d)\n", SMALL_BLOCK,
		(SMALL_BLOCK + BLOCK_SIZE) * 100 + ZONE_SIZE);
}

void    test_show_alloc_mem(void)
{
	char    *a;
    char    *b;
    char    *c;
    char    *d;

    a = malloc(42);
    b = malloc(84);
    c = malloc(3725);
    d = malloc(48847);
    printf("\n\n\n--- show_alloc_mem ---\n");
    show_alloc_mem();
    free(a);
    free(b);
    free(c);
    free(d);
    printf("\n\n\n");
    show_alloc_mem();
}

void    alone_show_alloc_mem(void)
{
	char    *a;
    char    *b;
    char    *c;
    char    *d;

    a = malloc(42);
    b = malloc(84);
    c = malloc(3725);
    d = malloc(48847);
    show_alloc_mem();
    free(a);
    free(b);
    free(c);
    free(d);
    show_alloc_mem();
}

int	main(void)
{
    //print_sizes();
    //test_show_alloc_mem();
    alone_show_alloc_mem();
	return (0);
}

