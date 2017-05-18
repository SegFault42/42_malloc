/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 05:59:09 by rabougue          #+#    #+#             */
/*   Updated: 2017/05/18 07:41:25 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/malloc.h"

t_block		g_block;

static void	*alloc_large(size_t size)
{
	void	*allocation_famillial;

	allocation_famillial = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (allocation_famillial == MALLOC_FAILURE)
	{
		ft_dprintf(2, "%s\n", strerror(errno));
		return (NULL);
	}
	return (allocation_famillial);
}

void	*malloc(size_t size)
{
	if (size <= TINY)
	{
		return (alloc_tiny(size));
	}
	return (alloc_large(size));
}

