/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 07:36:01 by rabougue          #+#    #+#             */
/*   Updated: 2017/05/19 05:52:21 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/malloc.h"

extern t_block *g_block;

/*bool	first_alloc_tiny(size_t size)*/
/*{*/
	/*int	i;*/

	/*i = -1;*/
	/*while (++i < 100)*/
	/*{*/
		/*g_block->ptr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);*/
		/*if (g_block->ptr == MALLOC_FAILURE)*/
		/*{*/
			/*ft_putstr_fd(strerror(errno), 2);*/
			/*return (false);*/
		/*}*/
	/*}*/
	/*return (true);*/
/*}*/

void	*alloc(size_t size, char flag)
{
	if (lst_push_back(g_block) != (int *)EXIT_SUCCESS)
		return (NULL);
	ft_putstr_fd("lst push back OK!\n", 1);
	return (lst_setup(size, flag));
	(void)size;
}
