/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz <molasz.dev@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 23:10:24 by molasz            #+#    #+#             */
/*   Updated: 2026/04/02 03:35:30 by molasz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

size_t	align16(size_t size)
{
	return ((size + 15) & ~15);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!n || dest == src)
		return (dest);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	write(1, s, i);
}

void	ft_putnbr(size_t n)
{
	char	c;

	if (n >= 10)
		ft_putnbr(n / 10);
	c = (n % 10) + '0';
	write(1, &c, 1);
}

void	ft_puthex(size_t n)
{
	char	*base;

	base = "0123456789ABCDEF";
	if (n >= 16)
		ft_puthex(n / 16);
	write(1, &base[n % 16], 1);
}

