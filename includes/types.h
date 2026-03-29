/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz <molasz.dev@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 00:36:53 by molasz            #+#    #+#             */
/*   Updated: 2026/03/29 03:17:01 by molasz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "malloc.h"
# include <unistd.h>
# include <sys/mman.h>

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
	struct s_block	*prev;
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

# define PAGE_SIZE 4096  // sysconf(_SC_PAGESIZE)

# define TINY_ZONE 16384
# define SMALL_ZONE 65536

# define TINY_BLOCK 128
# define SMALL_BLOCK 512

extern t_zone	*g_zones[3];

t_zone_type	get_type(size_t size);
t_zone		*find_or_create_zone(size_t size);

#endif
