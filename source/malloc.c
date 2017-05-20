/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 05:59:09 by rabougue          #+#    #+#             */
/*   Updated: 2017/05/20 04:56:47 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/malloc.h"

t_block		*g_block = NULL;
static int	g_i = 0;

static void	*alloc_large(size_t size)
{
	void	*alloc;

	alloc = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (alloc == MALLOC_FAILURE)
	{
		ft_putstr_fd(strerror(errno), 2);
		return (NULL);
	}
	else
	{
		if (g_i > 21)
		{
			ft_putstr_fd("\033[32mMMAP SUCCESS\n\033[0m", 1);
			RC;
		}
	}
	return (alloc);
}

void	*malloc(size_t size)
{
	++g_i;
	if (g_i == 22)
		ft_putstr_fd("=======================================================\n", 1);
	RC;
	ft_putstr_fd(ORANGE"iteration = "END, 1);
	ft_putnbr(g_i);
	RC;
	RC;
	ft_putstr_fd(CYAN"size = "END, 1);
	ft_putnbr(size);
	RC;
	if (size <= TINY)
	{
		ft_putstr_fd(CYAN"size = TINY"END, 2);
		return (alloc(size, 't'));
	}
	else if (size <= SMALL)
	{
		ft_putstr_fd(YELLOW"size = SMALL"END, 2);
		return (alloc(size, 's'));
	}
	else
	{
		write(1, "size = LARGE", 1);
		return (alloc_large(size));
	}
	return (NULL);
}

