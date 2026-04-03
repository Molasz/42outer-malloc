/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz <molasz.dev@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 02:05:57 by molasz            #+#    #+#             */
/*   Updated: 2026/04/03 02:17:54 by molasz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

void	test_tiny(void)
{
	void	*a;
	void	*b;
	void	*c;

	ft_putstr("\n --- TEST TINY (<= 128 bytes) ---\n");
	a = malloc(1);
	b = malloc(42);
	c = malloc(128);
	show_alloc_mem();
	free(a);
	free(b);
	free(c);
}

void	test_small(void)
{
	void	*a;
	void	*b;
	void	*c;

	ft_putstr("\n --- TEST SMALL (<= 4092 bytes) ---\n");
	a = malloc(129);
	b = malloc(1024);
	c = malloc(4092);
	show_alloc_mem();
	free(a);
	free(b);
	free(c);
}

void	test_large(void)
{
	void	*a;
	void	*b;

	ft_putstr("\n --- TEST LARGE (> 4092 bytes) ---\n");
	a = malloc(4093);
	b = malloc(100000);
	show_alloc_mem();
	free(a);
	free(b);
}

void	test_realloc(void)
{
	void	*a;
	void	*b;

	ft_putstr("\n --- TEST REALLOC ---\n");
	a = malloc(42);
	b = malloc(1024);
	show_alloc_mem();
	ft_putstr("\n - realloc -\n");
	a = realloc(a, 100);
	b = realloc(b, 5000);
	show_alloc_mem();
	free(a);
	free(b);
}

int	main(void)
{
	ft_putstr("\n --- COMPLETE ---\n");
	test_tiny();
	test_small();
	test_large();
	test_realloc();
	ft_putstr("\n --- FINAL ---\n");
	show_alloc_mem();
	return (0);
}
