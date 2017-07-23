/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   large.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/22 19:19:00 by rabougue          #+#    #+#             */
/*   Updated: 2017/07/23 19:36:19 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/malloc.h"

extern t_memory	g_memory;

static t_block	*norme(size_t *i)
{
	t_block	*tmp;

	tmp = g_memory.meta_large;
	while (tmp && tmp->free == 1)
	{
		tmp = tmp->next;
		++*i;
	}
	return (tmp);
}

static void		fill_lst_large(size_t ptr)
{
	t_block	*tmp;
	t_block	*tmp_2;
	size_t	i;

	i = 1;
	tmp_2 = g_memory.meta_large;
	tmp = norme(&i);
	if (tmp == NULL)
	{
		tmp = g_memory.meta_large;
		while (tmp)
			tmp = tmp->next;
		if (!tmp)
			return ;
		tmp->next = alloc_meta();
	}
	tmp_2 += i;
	tmp->next = tmp_2;
	tmp->ptr = g_memory.large_data + ptr;
	tmp->flag = 'l';
	if (tmp_2)
		tmp_2->next = NULL;
}

static t_block	*allocation(t_block *tmp, size_t size)
{
	if (g_memory.meta_large == NULL)
	{
		if ((g_memory.meta_large = alloc_meta()) == NULL)
			return (NULL);
	}
	if (alloc_data(size) == false)
		return (NULL);
	fill_lst_large(0);
	tmp = g_memory.meta_large;
	return (tmp);
}

void			*alloc_large(size_t size)
{
	t_block	*tmp;

	tmp = g_memory.meta_large;
	if ((tmp = allocation(tmp, size)) == NULL)
		return (NULL);
	tmp = g_memory.meta_large;
	while (tmp && tmp->free == 1)
		tmp = tmp->next;
	if (!tmp)
	{
		if (alloc_data(size) == false)
			return (NULL);
		fill_lst_large(0);
		tmp = g_memory.meta_large;
	}
	tmp->free = 1;
	tmp->size = size;
	return (tmp->ptr);
}
