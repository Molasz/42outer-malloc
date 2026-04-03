/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz <molasz.dev@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 00:36:53 by molasz            #+#    #+#             */
/*   Updated: 2026/04/03 02:21:45 by molasz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "malloc.h"
# include <unistd.h>
# include <sys/mman.h>
# include <pthread.h>

typedef enum e_zone_type
{
	TINY,
	SMALL,
	LARGE
}	t_zone_type;

typedef struct s_block
{
	size_t			size;
	struct s_block	*next;
	int				free;
}	t_block;

typedef struct s_zone
{
	size_t				total;
	size_t				used;
	struct s_zone		*next;
	t_block				*blocks;
}	t_zone;

# define BLOCK_SIZE 32 // ALIGN(sizeof(t_block))
# define ZONE_SIZE	32 // ALIGN(sizeof(t_zone))

# define TINY_BLOCK 128
# define SMALL_BLOCK 4092

extern t_zone			*g_zones[3];
extern pthread_mutex_t	g_malloc_mutex;

void		*call_malloc(size_t size);
void		call_free(void *ptr);

void		*call_mmap(size_t size);
void		call_munmap(t_zone *zone, t_zone *prev, t_zone_type type);

t_zone		*find_zone(size_t size);
t_block		*find_block(t_zone *zone, size_t size, size_t alsize);
void		fractionate_block(t_block *old, size_t size, size_t alsize);
void		coalesce_blocks(t_zone *zone);

size_t		align_size(size_t size, size_t align);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		ft_putstr(char *s);
void		ft_putnbr(size_t n);
void		ft_puthex(size_t n);

#endif
