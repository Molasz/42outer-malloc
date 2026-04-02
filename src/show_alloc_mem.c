/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz <molasz.dev@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 02:52:04 by molasz            #+#    #+#             */
/*   Updated: 2026/04/03 00:56:23 by molasz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

static void	ft_putaddr(void *addr)
{
	ft_putstr("0x");
	ft_puthex((size_t)addr);
}

static size_t	print_blocks(t_block *block)
{
	size_t	total;

	total = 0;
	while (block)
	{
		ft_putaddr((char *)(block + 1));
		ft_putstr(" - ");
		ft_putaddr((char *)(block + 1) + block->size);
		ft_putstr(" : ");
		ft_putnbr(block->size);
		if (block->free)
			ft_putstr(" \033[3mfree\033[0m");
		ft_putstr("\n");
		total += block->size;
		block = block->next;
	}
	return (total);
}

static size_t	print_zone(t_zone *zone, t_zone_type type)
{
	size_t	total;

	total = 0;
	while (zone)
	{
		if (type == TINY)
			ft_putstr("TINY : ");
		else if (type == SMALL)
			ft_putstr("SMALL : ");
		else
			ft_putstr("LARGE : ");
		ft_putaddr(zone);
		ft_putstr("\n");
		total += print_blocks(zone->blocks);
		zone = zone->next;
	}
	return (total);
}

static size_t	print_zones(void)
{
	t_zone	*zone;
	size_t	total;
	int		type;

	type = 0;
	total = 0;
	while (type < 3)
	{
		zone = g_zones[type];
		total += print_zone(zone, type);
		type++;
	}
	return (total);
}

void	show_alloc_mem(void)
{
	size_t	total;

	total = print_zones();
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putstr(" bytes\n");
}
