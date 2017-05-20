/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 01:44:28 by rabougue          #+#    #+#             */
/*   Updated: 2017/05/20 05:52:33 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/malloc.h"

extern t_block *g_block;

void *create_memory(size_t size)
{
	void *node;

	node = NULL;
	if (size <= TINY)
		node = mmap(0, (TINY * 128) - 40, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	else if (size <= SMALL)
		node = mmap(0, (SMALL * 128) - 40, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (node == MALLOC_FAILURE)
	{
		ft_putstr_fd(RED"MMAP FAILURE\n"END, 2);
		ft_putstr_fd(strerror(errno), 2);
		return (NULL);
	}
	ft_putstr_fd(GREEN"MMAP SUCCESS\n"END, 1);
	ft_memset(node, 0, size);
	return (node);
}

void *lst_setup(size_t size, char flag)
{
	t_block *tmp;

	tmp = g_block;
	if (tmp == NULL)
		ft_putstr_fd("\ntmp == NULL", 2);
	while (tmp->next)
		tmp = tmp->next;
	if ((tmp->ptr = create_memory(size)) != NULL)
	{
		tmp->flag = flag;
		tmp->size = size;
		tmp->next = NULL;
		if (tmp->prev != g_block)
			tmp->prev = tmp;
		else
			tmp->prev = NULL;
	}
	return (tmp->ptr);

}
void *lst_push_back()
{
	t_block	*tmp;

	tmp = g_block;
	if (!tmp)
	{
		if ((g_block = create_node()) == NULL)
		{
			ft_putstr_fd(RED"\nCreate g_block FAILURE !\n"END, 2);
			return (NULL);
		}
		ft_putstr_fd(GREEN"\nCreate g_block (first time) SUCCESS !\n"END, 2);
		return ((int *)EXIT_SUCCESS);
	}
	while (tmp->next)
		tmp = tmp->next;
	if (tmp->next == NULL)
		tmp->next = create_node();
	if (tmp->next == NULL)
	{
		ft_putstr_fd(RED"\nCreate g_block FAILURE !\n"END, 2);
		return (NULL);
	}
	ft_putstr_fd(GREEN"\nCreate g_block  SUCCESS !\n"END, 2);
	return ((int *)EXIT_SUCCESS);
}

t_block	*create_node()
{
	t_block	*node;

	node = mmap(0, sizeof(t_block), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (node == MALLOC_FAILURE)
	{
		ft_putstr_fd(RED"\nMMAP failure (create node)\n"END, 2);
		return (NULL);
	}
	ft_memset(node, 0, sizeof(t_block));
	return (node);
}
