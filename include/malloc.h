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
# include <sys/time.h>
# include <sys/mman.h>
# include <sys/resource.h>
# include "../libft/includes/libft.h"

# define MALLOC_FAILURE	(void *) -1
# define TINY			64
# define SMALL			256

typedef struct		s_block
{
	size_t			size;		// size of allocation
	struct s_block	*next;		// next pointer
	void			*ptr;		// pointer on data
	bool			free;		// free or not
	char			data[1];	// ???
	char			flag;		// flag size (tiny, small or large)
	char			pad[5];		// variable for padding
}					t_block;
/*
** tiny.c
*/
bool	*first_alloc_tiny(size_t size);
void	*alloc(size_t size, char flag);
/*
** malloc.c
*/
void	*malloc(size_t size);
void free(void *ptr);
/*
** lst.c
*/
t_block	*create_node();
void	*lst_push_back();
void	*create_memory(size_t size);
void	*lst_setup(size_t size, char flag);
/*
** show_alloc_mem.c
*/
void	show_alloc_mem();

#endif
