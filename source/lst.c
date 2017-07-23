/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/22 19:18:54 by rabougue          #+#    #+#             */
/*   Updated: 2017/07/23 19:42:18 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/malloc.h"

extern t_memory	g_memory;

static void	init_node(t_block *node, char flag, int i)
{
	void	*tmp;

	tmp = NULL;
	if (flag == 't')
	{
		tmp = g_memory.tiny_data;
		tmp += i * TINY;
	}
	else if (flag == 's')
	{
		tmp = g_memory.small_data;
		tmp += i * SMALL;
	}
	node->ptr = tmp;
	node->flag = flag;
}

bool		check_if_meta_full(size_t size)
{
	t_block	*tmp;

	if (size <= TINY)
		tmp = g_memory.meta_tiny;
	else
		tmp = g_memory.meta_small;
	while (tmp && tmp->free == 1)
		tmp = tmp->next;
	if (tmp->next == NULL)
		return (LST_FULL);
	return (LST_NOT_FULL);
}

static void	norme(t_block *tmp, t_block *tmp_2, char flag)
{
	uint8_t	i;

	i = 0;
	init_node(tmp, flag, i);
	++i;
	++tmp;
	while (i < NB_ZONES)
	{
		tmp_2->next = tmp;
		++tmp_2;
		init_node(tmp, flag, i);
		++tmp;
		++i;
	}
}

void		fill_lst(char flag)
{
	t_block	*tmp;
	t_block	*tmp_2;

	tmp = NULL;
	tmp_2 = NULL;
	if (flag == 't')
	{
		tmp = g_memory.meta_tiny;
		while (tmp->next)
			tmp = tmp->next;
		tmp_2 = tmp;
	}
	else
	{
		tmp = g_memory.meta_small;
		while (tmp->next)
			tmp = tmp->next;
		tmp_2 = tmp;
	}
	norme(tmp, tmp_2, flag);
}
