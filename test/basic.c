/* ************************************************************************** */
/*		                                                                      */
/*                                                        :::      ::::::::   */
/*   basic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz <molasz.dev@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 01:31:41 by molasz            #+#    #+#             */
/*   Updated: 2026/04/03 02:18:02 by molasz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include <stdio.h>

static void	show_alloc_mem_test_normal(void)
{
	char	*a;
	char	*b;
	char	*c;
	char	*d;

	a = malloc(42);
	b = malloc(84);
	c = malloc(3725);
	d = malloc(48847);
	show_alloc_mem();
	free(a);
	free(b);
	free(c);
	free(d);
}

static void	show_alloc_mem_test_basic(void)
{
	char	*a;
	char	*b;
	char	*c;
	char	*d;

	ft_putstr("\n\n\n --- EXTRA ---\n\n\n");
	a = malloc(42);
	b = malloc(84);
	c = malloc(3725);
	d = malloc(48847);
	show_alloc_mem();
	ft_putstr("\n\n\n --- REALLOC ---\n\n\n");
	a = realloc(a, 65);
	b = realloc(b, 12);
	c = realloc(c, 2026);
	d = realloc(d, 48848);
	show_alloc_mem();
	free(a);
	free(b);
	free(c);
	free(d);
	ft_putstr("\n\n\n --- FREE ---\n\n\n");
	show_alloc_mem();
}

int	main(void)
{
	show_alloc_mem_test_normal();
	show_alloc_mem_test_basic();
	return (0);
}
