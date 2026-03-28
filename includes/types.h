/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz <molasz.dev@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 00:36:53 by molasz            #+#    #+#             */
/*   Updated: 2026/03/28 02:08:22 by molasz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES__H
# define TYPES__H

# include "malloc.h"
# include <unistd.h>
# include <sys/mman.h>

typedef struct s_block
{
	size_t			size;
	struct s_block	*next;
	int				free;
} t_block;

typedef struct s_area
{
	size_t			type;
	size_t			total;
	struct s_area	*next;
	t_block			*top;
} t_area;

# define ALIGNMENT 16
# define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))

# define BLOCK_SIZE ALIGN(sizeof(t_block))
# define AREA_SIZE	ALIGN(sizeof(t_area))

# ifdef __APPLE__
#  define PAGE_SIZE getpagesize()
# else
#  define PAGE_SIZE sysconf(_SC_PAGESIZE)
# endif

# define TINY_ZONE (PAGE_SIZE * 4)
# define SMALL_ZONE (PAGE_SIZE * 16)


# define TINY_BLOCK 128
# define SMALL_BLOCK 512

extern t_area *g_areas;

#endif
