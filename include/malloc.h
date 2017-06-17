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
# define TINY			64
# define SMALL			256
# define LST_FULL		1
# define LST_NOT_FULL	0
# define NB_ZONES		1

# define DEBUG_CALLING_MALLOC		1
# define DEBUG_PRINT_NODE			0
# define DEBUG_CALLING_FREE_MESSAGE	0
# define DEBUG_ADDRESS_TO_FREE		0
# define DEBUG_FREE_CURRENT_ADDR	0
# define DEBUG_PRINT_INFO_NODE		0
# define DEBUG_SHOW_RET_MMAP		0
# define DEBUG_PRINT_CTRL_G_BLOCK	0

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

void	DEBUG_calling_malloc();
void	DEBUG_print_node(t_block *node, t_block * node2, t_block *node3, int i);
void	DEBUG_calling_free_message();
void	DEBUG_address_to_free(void *addr);
void	DEBUG_free_current_addr(void *ptr, size_t i);
void	DEBUG_print_info_node(size_t i);
void	DEBUG_show_ret_mmap(int ret);
void	DEBUG_print_ctrl_g_tiny(t_block *ctrl, t_block *g_block);

void	show_alloc_mem();
#endif
