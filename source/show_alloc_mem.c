/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 05:05:08 by rabougue          #+#    #+#             */
/*   Updated: 2017/05/19 06:03:43 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/malloc.h"

extern t_block	*g_block;

void	show_alloc_mem()
{
	t_block		*tmp;
	static int	i = 0;

	tmp = g_block;
	while (tmp->next)
	{
	ft_putnbr(i);
	RC;
		if (i >= 21 && tmp->flag == 't')
		{
			ft_putstr_fd("TINY : ", 1);
			print_hexa((unsigned long)tmp->ptr);
			RC;
		}
		++i;
		tmp = tmp->next;
	}
}
