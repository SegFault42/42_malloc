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
# define LST_FULL		1
# define LST_NOT_FULL	0

typedef struct		s_block
{
	struct s_block	*next;		// next pointer
	size_t			size;		// size of allocation
	void			*ptr;		// pointer on data
	bool			free;		// free or not
	char			data[1];	// ???
	char			flag;		// flag size (tiny, small or large)
	char			pad[5];		// variable for padding
}					t_block;

typedef struct		s_ctrl
{
	t_block			*first;
}					t_ctrl;
#endif
