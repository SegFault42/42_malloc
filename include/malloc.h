/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 05:54:47 by rabougue          #+#    #+#             */
/*   Updated: 2017/05/18 07:37:53 by rabougue         ###   ########.fr       */
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
	struct s_block	*prev;		// prev pointer
	void			*ptr;		// pointer on data
	bool			free;		// free or not
	char			data[1];	// ???
	char			pad[3];		// variable for padding
}					t_block;

void	*alloc_tiny(size_t size);
void	*malloc(size_t size);

#endif
