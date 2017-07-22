/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/22 19:19:09 by rabougue          #+#    #+#             */
/*   Updated: 2017/07/22 20:27:54 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/malloc.h"

extern t_memory	g_memory;
extern t_mutex	g_mutex;

void			save_alloc_history(size_t size, void *allocation)
{
	static size_t	i = 1;
	int				fd;

	if (i == 1)
		fd = open("Malloc_history", O_RDWR | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR);
	else
		fd = open("Malloc_history", O_RDWR | O_CREAT | O_APPEND,
				S_IRUSR | S_IWUSR);
	if (fd != -1)
	{
		ft_putstr_fd(CYAN"Malloc_call : ", fd);
		ft_putnbr_fd(i, fd);
		ft_putstr_fd(ORANGE" Size :", fd);
		ft_putnbr_fd(size, fd);
		ft_putstr_fd(GREEN" Addr :", fd);
		print_hexa_fd((unsigned int)allocation, fd);
		ft_putendl_fd(""END, fd);
		close(fd);
		++i;
	}
}

void			show_consum(size_t size)
{
	static size_t	size_total = 0;

	size_total += size;
	ft_putendl("=====================================");
	ft_putstr(PINK"Memory allocated in  B : ");
	ft_putnbr(size_total);
	RC;
	ft_putstr(GREEN"Memory allocated in KB : ");
	ft_putnbr(size_total / 1024);
	RC;
	ft_putstr(ORANGE"Memory allocated in MB : ");
	ft_putnbr(size_total / 1024 / 1024);
	RC;
	ft_putstr(RED"Memory allocated in GB : ");
	ft_putnbr(size_total / 1024 / 1024 /1024);
	ft_putendl("\n"END);
}

void			debug_env(size_t size, void *allocation)
{
	if (getenv("MALLOC_HISTORY") && !ft_strcmp(getenv("MALLOC_HISTORY"), "1"))
		save_alloc_history(size, allocation);
	if (getenv("MALLOC_SHOW_CONSUM") &&
			!ft_strcmp(getenv("MALLOC_SHOW_CONSUM"), "1"))
		show_consum(size);
}

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
	{
		ft_putstr(YELLOW"\e[1mTINY : ");
		print_hexa_fd((unsigned int)g_memory.meta_tiny, 2);
		RC;
		total += print_data_mem(g_memory.meta_tiny);
	}
	if (g_memory.meta_small && g_memory.meta_small->free == 1)
	{
		ft_putstr(ORANGE"SMALL : ");
		print_hexa_fd((unsigned int)g_memory.meta_small, 2);
		RC;
		total += print_data_mem(g_memory.meta_small);
	}
	if (g_memory.meta_large && g_memory.meta_large->free == 1)
	{
		ft_putstr(RED"LARGE : ");
		print_hexa_fd((unsigned int)g_memory.meta_large, 2);
		RC;
		total += print_data_mem(g_memory.meta_large);
	}
	ft_putstr(PURPLE"Total : ");
	ft_putnbr(total);
	ft_putendl(" octets"END);
	pthread_mutex_unlock(&g_mutex.m_show_alloc_mem);
}
