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
# include "../libft/includes/libft.h"

# define MALLOC_FAILURE	(void *) -1
# define TINY			(64)
//# define TINY			(128)
# define SMALL			(1024)
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

void	DEBUG_print_allocated_zones();
void	show_alloc_mem();

#endif
