/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/22 19:19:09 by rabougue          #+#    #+#             */
/*   Updated: 2017/07/23 18:53:05 by rabougue         ###   ########.fr       */
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
	ft_putnbr(size_total / 1024 / 1024 / 1024);
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
