/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stress.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz <molasz.dev@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 02:00:03 by molasz            #+#    #+#             */
/*   Updated: 2026/04/03 02:29:09 by molasz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "types.h"

void	test_stress_tiny(void)
{
	void	*arr[100];
	int		i;

	ft_putstr("\n --- STRESS TINY (100 * 128b) ---\n");
	i = 0;
	while (i < 100)
	{
		arr[i] = malloc(128);
		i++;
	}
	show_alloc_mem();
	i = 0;
	while (i < 100)
	{
		free(arr[i]);
		i++;
	}
}

void	test_stress_small(void)
{
	void	*arr[50];
	int		i;

	ft_putstr("\n --- STRESS SMALL (50 * 1024b) ---\n");
	i = 0;
	while (i < 50)
	{
		arr[i] = malloc(1024);
		i++;
	}
	show_alloc_mem();
	i = 0;
	while (i < 50)
	{
		free(arr[i]);
		i++;
	}
}

void	test_stress_large(void)
{
	void	*arr[10];
	int		i;

	ft_putstr("\n --- STRESS LARGE (10 * 100000b) ---\n");
	i = 0;
	while (i < 10)
	{
		arr[i] = malloc(100000);
		i++;
	}
	show_alloc_mem();
	i = 0;
	while (i < 10)
	{
		free(arr[i]);
		i++;
	}
}

void	test_stress_realloc(void)
{
	void	*arr[20];
	int		i;

	ft_putstr("\n --- STRESS REALLOC (TINY -> SMALL) ---\n");
	i = 0;
	while (i < 20)
	{
		arr[i] = malloc(10);
		i++;
	}
	i = 0;
	while (i < 20)
	{
		arr[i] = realloc(arr[i], 2000);
		i++;
	}
	show_alloc_mem();
	i = 0;
	while (i < 20)
	{
		free(arr[i]);
		i++;
	}
}

int	main(void)
{
	ft_putstr("\n --- STRESS ---\n");
	test_stress_tiny();
	test_stress_small();
	test_stress_large();
	test_stress_realloc();
	ft_putstr("\n --- FINAL ---\n");
	show_alloc_mem();
	return (0);
}
