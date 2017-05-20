/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 05:05:08 by rabougue          #+#    #+#             */
/*   Updated: 2017/05/20 08:25:13 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/malloc.h"

extern t_block	*g_block;

void	show_alloc_mem()
{
	t_block		*tmp;
	static int	i = 0;

	tmp = g_block;
	while (tmp)
	{
		if (i >= 21 && tmp->flag == 't')
		{
			if (i == 21)
			{
				ft_putstr_fd(CYAN"TINY : "PURPLE, 1);
				print_hexa((unsigned long)tmp->ptr);
				ft_putstr_fd(END"", 1);
				RC ;
			}
			print_hexa((unsigned long)tmp->ptr + sizeof(t_block));
			ft_putstr_fd(" - ", 1);
			print_hexa((unsigned long)tmp->ptr + sizeof(t_block) + tmp->size);
			ft_putstr_fd(" : ", 1);
			ft_putnbr(tmp->size);
			RC;
		}
		tmp = tmp->next;
		++i;
	}
}
