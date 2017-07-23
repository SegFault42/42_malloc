/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/23 18:48:38 by rabougue          #+#    #+#             */
/*   Updated: 2017/07/23 19:20:41 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/malloc.h"

extern t_memory	g_memory;
extern t_mutex	g_mutex;

static size_t	print_data_mem(t_block *zone)
{
	size_t	total;

	total = 0;
	while (zone)
	{
		if (zone->free == 1)
		{
			print_hexa_fd((unsigned int)zone->ptr, 2);
			ft_putstr(" - ");
			print_hexa_fd((unsigned int)zone->ptr + zone->size, 2);
			ft_putstr(" : ");
			ft_putnbr(zone->size);
			ft_putendl(" octets");
			total += zone->size;
		}
		zone = zone->next;
	}
	RC;
	return (total);
}

static size_t	size(char flag)
{
	if (flag == 't')
	{
		ft_putstr(YELLOW"\e[1mTINY : ");
		print_hexa_fd((unsigned int)g_memory.meta_tiny, 2);
		RC;
		return (print_data_mem(g_memory.meta_tiny));
	}
	else if (flag == 's')
	{
		ft_putstr(ORANGE"SMALL : ");
		print_hexa_fd((unsigned int)g_memory.meta_small, 2);
		RC;
		return (print_data_mem(g_memory.meta_small));
	}
	else
	{
		ft_putstr(RED"LARGE : ");
		print_hexa_fd((unsigned int)g_memory.meta_large, 2);
		RC;
		return (print_data_mem(g_memory.meta_large));
	}
}

void			show_alloc_mem(void)
{
	size_t	total;

	total = 0;
	if (pthread_mutex_lock(&g_mutex.m_show_alloc_mem) == EINVAL)
	{
		pthread_mutex_init(&g_mutex.m_show_alloc_mem, NULL);
		pthread_mutex_lock(&g_mutex.m_show_alloc_mem);
	}
	if (g_memory.meta_tiny && g_memory.meta_tiny->free == 1)
		total += size('t');
	if (g_memory.meta_small && g_memory.meta_small->free == 1)
		total += size('s');
	if (g_memory.meta_large && g_memory.meta_large->free == 1)
		total += size('l');
	ft_putstr(PURPLE"Total : ");
	ft_putnbr(total);
	ft_putendl(" octets"END);
	pthread_mutex_unlock(&g_mutex.m_show_alloc_mem);
}
