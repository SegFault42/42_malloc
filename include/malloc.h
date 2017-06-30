/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 05:54:47 by rabougue          #+#    #+#             */
/*   Updated: 2017/05/20 02:14:40 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <errno.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/mman.h>
# include <string.h>
# include <pthread.h>
# include "../libft/includes/libft.h"

# define MALLOC_FAILURE	(void *) -1
# define TINY			(1024)
# define SMALL			(4096)
# define LST_FULL		(1)
# define LST_NOT_FULL	(0)
# define NB_ZONES		(128)
# define MAX_SIZE		(SIZE_T_MAX - (2 * getpagesize()))

# define PROT			PROT_READ | PROT_WRITE
# define FLAG			MAP_ANON | MAP_PRIVATE

typedef struct		s_block
{
	struct s_block	*next;		// next pointer
	size_t			size;		// size of allocation
	void			*ptr;		// pointer on data
	bool			free;		// free or not
	char			flag;		// flag size (tiny, small or large)
	char			pad[6];		// variable for padding
}					t_block;

typedef	struct		s_memory
{
	t_block			*meta_tiny;
	t_block			*meta_small;
	t_block			*meta_large;
	void			*tiny_data;
	void			*small_data;
	void			*large_data;
}					t_memory;

typedef struct		s_mutex
{
	pthread_mutex_t	m_malloc;
	pthread_mutex_t	m_calloc;
	pthread_mutex_t	m_realloc;
	pthread_mutex_t	m_free;
	pthread_mutex_t	m_show_alloc_mem;
}					t_mutex;

void				show_alloc_mem();
/*
**	realloc.c
*/
void				*realloc(void *ptr, size_t size);
/*
**	free.c
*/
void				free(void *addr);
/*
**	debug.c
*/
void				show_alloc_mem();
void				DEBUG_print_allocated_zones();
void				debug_env();
/*
**	tiny_small.c
*/
void				*alloc_tiny_small(size_t size);
/*
**	tiny_small.c
*/
void				*alloc_large(size_t size);
/*
**	lst.c
*/
bool				check_if_meta_full(size_t size);
void				fill_lst(char flag);
/*
**	memory.c
*/
t_block				*alloc_meta();
bool				alloc_data(size_t size);

#endif
