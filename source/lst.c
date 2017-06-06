/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 01:44:28 by rabougue          #+#    #+#             */
/*   Updated: 2017/05/20 09:57:21 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/malloc.h"

extern t_block *g_block;

size_t	calc_size_to_alloc(size_t size)
{
	size_t	final_size;
	size_t	modulo;
	size_t	arrondie;

	if (size <= TINY)
	{
		final_size = TINY;
		final_size += sizeof(t_block);
		final_size *= 128; // number of allocation
	}
	else
	{
		final_size = SMALL;
		final_size += sizeof(t_block);
		final_size *= 128; // number of allocation
	}
	modulo = final_size % getpagesize();
	if (modulo)
	{
		arrondie = getpagesize() - modulo;
		final_size += arrondie;
	}
	ft_putnbr(final_size);
	return (final_size);
}

void	count_nb_octet_free()
{
	t_block	*tmp;
	/*unsigned long	nb_octet;*/
	int	i = 0;

	tmp = g_block;
	while (tmp->next)
	{
		if (i >= 21)
		{
			print_hexa((unsigned long)tmp->ptr);
		}
		++i;
		tmp = tmp->next;
	}
	/*nb_octet = (unsigned long)tmp->ptr - nb_octet;*/
	RC;
}

void *create_memory(size_t size)
{
	void *node;

	node = NULL;
	node = mmap(0, calc_size_to_alloc(size), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (node == MALLOC_FAILURE)
	{
		ft_putstr_fd(RED"MMAP FAILURE\n"END, 2);
		ft_putstr_fd(strerror(errno), 2);
		return (NULL);
	}
	ft_putstr_fd(GREEN"MMAP SUCCESS\n"END, 1);
	/*count_nb_octet_free();*/
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
