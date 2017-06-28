#include "../include/malloc.h"

t_memory	g_memory = {NULL, NULL, NULL, NULL, NULL, NULL};

t_block	*look_for_ptr(void *ptr)
{
	t_block	*tmp;
	uint8_t	i;

	i = 0;
	tmp = g_memory.meta_tiny;
	while (i < 3)
	{
		if (i == 1)
			tmp = g_memory.meta_small;
		else if (i == 2)
			tmp = g_memory.meta_large;
		while (tmp)
		{
			if (tmp->ptr == ptr)
				return (tmp);
			tmp = tmp->next;
		}
		++i;
	}
	return (NULL);
}

void	*realloc(void *ptr, size_t size)
{
	void	*tmp;
	void	*allocation_familliale;
	t_block	*tmp_meta;

	tmp = ptr;
	allocation_familliale = NULL;
	/*ft_putendl("Realloc");*/
	if (ptr == NULL)
	{
		/*ft_putendl("ptr = NULL");*/
		allocation_familliale = malloc(size);
		return (allocation_familliale);
	}
	if (size == 0 && ptr)
	{
		/*ft_putendl("size = 0");*/
		free(ptr);
		return (NULL);
	}
	tmp_meta = look_for_ptr(ptr);
	if (tmp_meta == NULL)
		return (NULL);
	if ((size <= TINY && tmp_meta->size <= TINY) ||
		(size <= SMALL && tmp_meta->size <= SMALL) ||
		(size <= tmp_meta->size + (tmp_meta->size % getpagesize()) && size > SMALL))
		{
		/*ft_putendl("if");*/
		return (ptr);
		}
	else
	{
		allocation_familliale = malloc(size);
		/*ft_putstr("else");*/
		if (allocation_familliale)
		{
			/*ft_putstr(" ok");*/
			if (size < tmp_meta->size)
				ft_memcpy(allocation_familliale, ptr, size);
			else
				ft_memcpy(allocation_familliale, ptr, tmp_meta->size);
		}
		free(ptr);
		/*RC;*/
	}

	return (allocation_familliale);
}

bool	look_for_addr(void *addr)
{
	t_block	*tmp;
	int		i;

	i = 0;
	tmp = g_memory.meta_tiny;
	while (i < 2)
	{
		while (tmp)
		{
			if (tmp->ptr == addr)
			{
				tmp->free = 0;
				tmp->size = 0;
				tmp->flag = 0;
				return (true);
			}
			tmp = tmp->next;
		}
		++i;
		tmp = g_memory.meta_small;
	}
	return (false);
}

void	free_large(void *addr)
{
	t_block	*tmp;

	tmp = g_memory.meta_large;
	while (tmp)
	{
		if (tmp->ptr == addr)
		{
			/*if ((size_t)tmp->ptr % getpagesize() == 0 && munmap(tmp->ptr, tmp->size) != 0)*/
			/*{*/
				/*ft_putstr_fd("munmap error : ", 2);*/
				/*ft_putendl_fd(strerror(errno), 2);*/
			/*}*/
			if (munmap(tmp->ptr, tmp->size) == -1)
			{
				/*ft_putstr_fd("munmap error : ", 2);*/
				/*ft_putendl_fd(strerror(errno), 2);*/
			}
			tmp->free = 0;
			tmp->ptr = NULL;
			tmp->size = 0;
			tmp->flag = 0;
			return ;
		}
		/*tmp_2 = tmp;*/
		tmp = tmp->next;
	}
}

void	free(void *addr)
{
	/*ft_putendl("Free");*/
	if (addr == NULL)
		return ;
	if (look_for_addr(addr) == true)
		return ;
	else
		free_large(addr);
}

bool	check_if_meta_full(size_t size)
{
	t_block	*tmp;

	if (size <= TINY)
		tmp = g_memory.meta_tiny;
	else
		tmp = g_memory.meta_small;
	while (tmp->next && tmp->free == 1)
		tmp = tmp->next;
	if (tmp->next == NULL)
		return (LST_FULL);
	return (LST_NOT_FULL);
}

size_t	print_data_mem(t_block *zone)
{
	size_t	total;

	total = 0;
	while (zone)
	{
		if (zone->free == 1)
		{
			print_hexa((unsigned int)zone->ptr);
			ft_putstr(" - ");
			print_hexa((unsigned int)zone->ptr + zone->size);
			ft_putstr(" : ");
			ft_putnbr(zone->size);
			ft_putendl(" octets");
			total += zone->size;
		}
		zone = zone->next;
		/*print_hexa((unsigned int)zone);*/
		/*RC;*/
	}
	RC;
	return (total);
}

void	show_alloc_mem()
{
	size_t	total;

	total = 0;
	if (g_memory.meta_tiny && g_memory.meta_tiny->free == 1)
	{
		ft_putstr(YELLOW"\e[1mTINY : ");
		print_hexa((unsigned int)g_memory.meta_tiny);
		RC;
		total += print_data_mem(g_memory.meta_tiny);
	}
	if (g_memory.meta_small && g_memory.meta_small->free == 1)
	{
		ft_putstr(ORANGE"SMALL : ");
		print_hexa((unsigned int)g_memory.meta_small);
		RC;
		total += print_data_mem(g_memory.meta_small);
	}
	if (g_memory.meta_large && g_memory.meta_large->free == 1)
	{
		ft_putstr(RED"LARGE : ");
		print_hexa((unsigned int)g_memory.meta_large);
		RC;
		total += print_data_mem(g_memory.meta_large);
	}
	ft_putstr(PURPLE"Total : ");
	ft_putnbr(total);
	ft_putendl(" octets"END);
}

bool	alloc_data(size_t size)
{
	if (size <= TINY)
	{
		g_memory.tiny_data = mmap(NULL, TINY * 128, PROT, FLAG, -1, 0);
		if (g_memory.tiny_data == NULL)
		{
			ft_putstr_fd(strerror(errno), 2);
			return (false);
		}
		/*ft_memset(g_memory.tiny_data, 0, TINY * 128);*/
	}
	else if (size <= SMALL)
	{
		g_memory.small_data = mmap(NULL, SMALL * 128, PROT, FLAG, -1, 0);
		if (g_memory.small_data == NULL)
		{
			ft_putstr_fd(strerror(errno), 2);
			return (false);
		}
		/*ft_memset(g_memory.small_data, 0, SMALL * 128);*/
	}
	else
	{
		g_memory.large_data = mmap(NULL, size, PROT, FLAG, -1, 0);
		if (g_memory.large_data == NULL)
		{
			ft_putstr_fd(strerror(errno), 2);
			return (false);
		}
		/*ft_memset(g_memory->large_data, 0, size);*/
	}
	return (true);
}

t_block	*alloc_meta()
{
	t_block	*tmp;

	tmp = mmap(NULL, getpagesize(), PROT, FLAG, -1, 0);
	if (tmp == NULL)
	{
		ft_putstr_fd(strerror(errno), 2);
		return (NULL);
	}
	ft_memset(tmp, 0, getpagesize());
	return (tmp);
}

void	init_node(t_block *node, char flag, int i)
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

void	fill_lst(char flag)
{
	uint8_t	i;
	t_block	*tmp;
	t_block	*tmp_2;

	i = 0;
	tmp = NULL;
	tmp_2 = NULL;
	if (flag == 't')
	{
		tmp = g_memory.meta_tiny;
		while (tmp->next)
			tmp = tmp->next;
		tmp_2 = tmp;
	}
	else if (flag == 's')
	{
		tmp = g_memory.meta_small;
		while (tmp->next)
			tmp = tmp->next;
		tmp_2 = tmp;
	}
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

void	*alloc_tiny_small(size_t size)
{
	t_block	*tmp;

	tmp = NULL;
	if (size <= TINY)
	{
		if (g_memory.meta_tiny == NULL)
		{
			if ((g_memory.meta_tiny = alloc_meta()) == NULL)
				return (NULL);
			if (alloc_data(size) == false)
				return (NULL);
			fill_lst('t');
		}
		else if (check_if_meta_full(size) == LST_FULL)
		{
			tmp = g_memory.meta_tiny;
			while (tmp->next)
				tmp = tmp->next;
			if ((tmp->next = alloc_meta()) == NULL)
				return (NULL);
			if (alloc_data(size) == false)
				return (NULL);
			fill_lst('t');
		}
		tmp = g_memory.meta_tiny;
	}
	else if (size <= SMALL)
	{
		if (g_memory.meta_small == NULL)
		{
			if ((g_memory.meta_small = alloc_meta()) == NULL)
				return (NULL);
			if (alloc_data(size) == false)
				return (NULL);
			fill_lst('s');
		}
		else if (check_if_meta_full(size) == LST_FULL)
		{
			tmp = g_memory.meta_small;
			while (tmp->next)
				tmp = tmp->next;
			if ((tmp->next = alloc_meta()) == NULL)
				return (NULL);
			if (alloc_data(size) == false)
				return (NULL);
			fill_lst('s');
		}
		tmp = g_memory.meta_small;
	}
	while (tmp->next && tmp->free == 1)
		tmp = tmp->next;
	tmp->free = 1;
	tmp->size = size;
	return (tmp->ptr);
}

void	fill_lst_large(size_t ptr)
{
	t_block	*tmp;
	t_block	*tmp_2;
	size_t	i;

	i = 1;
	tmp = g_memory.meta_large;
	tmp_2 = g_memory.meta_large;
	while (tmp && tmp->free == 1)
	{
		tmp = tmp->next;
		++i;
	}
	if (tmp == NULL)
	{
		tmp = g_memory.meta_large;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = alloc_meta();
	}
	tmp_2 += i;
	tmp->next = tmp_2;
	tmp->ptr = g_memory.large_data + ptr;
	tmp->flag = 'l';
	if (tmp_2)
		tmp_2->next = NULL;
}

size_t	check_if_alloc_fill(size_t size)
{
	t_block	*tmp;
	size_t	begin_page;
	size_t	i;
	size_t	size_alloc_in_page;

	begin_page = 1;
	i = 1;
	tmp = g_memory.meta_large;
	size_alloc_in_page = 0;
	/*ft_putstr("a\n");*/
	while (tmp && tmp->free == 1)
	{
		if ((int)tmp->ptr % getpagesize() == 0)
			begin_page = i;
		++i;
		tmp = tmp->next;
	}
	/*ft_putstr("b\n");*/
	tmp = g_memory.meta_large;
	/*i = 1;*/
	/*while (i < begin_page)*/
	/*{*/
		/*tmp = tmp->next;*/
		/*++i;*/
	/*}*/
	tmp += begin_page;
	while (tmp && tmp->free == 1)
	{
		size_alloc_in_page += tmp->size;
		tmp = tmp->next;
	}
	if (getpagesize() - size_alloc_in_page >= size)
	{
		return (size_alloc_in_page);
	}
	return (0);
}

void	*alloc_large(size_t size)
{
	t_block	*tmp;
	size_t	addr_ok;

	tmp = g_memory.meta_large;
	addr_ok = 0;
	if (g_memory.meta_large == NULL)
	{
		if ((g_memory.meta_large = alloc_meta()) == NULL)
			return (NULL);
		if (alloc_data(size) == false)
			return (NULL);
		fill_lst_large(0);
		tmp = g_memory.meta_large;
	}
	else
	{
		if ((addr_ok = check_if_alloc_fill(size)) == 0)
		{
			if (alloc_data(size) == false)
				return (NULL);
			fill_lst_large(0);
		}
		else
			fill_lst_large(addr_ok);
	}
	while (tmp && tmp->free == 1)
	{
		tmp = tmp->next;
		/*print_hexa((unsigned int )tmp);*/
		/*RC;*/
	}
	if (!tmp)
	{
		if (alloc_data(size) == false)
			return (NULL);
		fill_lst_large(0);
		tmp = g_memory.meta_large;
	}
	tmp->free = 1;
	tmp->size = size;
	/*print_hexa((unsigned int)tmp->ptr);*/
	return (tmp->ptr);
}

void	*calloc(size_t nmemb, size_t size)
{
	void	*allocation_familliale;
	/*ft_putendl("Calloc");*/

	allocation_familliale = NULL;
	if (size > MAX_SIZE || size == 0 || nmemb == 0)
		return (allocation_familliale);
	allocation_familliale = malloc(nmemb * size);
	ft_memset(allocation_familliale, 0, nmemb * size);
	return (allocation_familliale);
}

void	*malloc(size_t size)
{
	void	*allocation_familliale;

	/*ft_memset(&g_memory, 0, sizeof(g_memory));*/
	/*static size_t	nb_alloc_tiny = 0;*/
	/*static size_t	nb_alloc_small = 0;*/
	/*static size_t	nb_alloc_large = 0;*/

	/*++nb_alloc_tiny;*/
	/*ft_putstr("Size = ");*/
	/*ft_putnbr(size);*/
	/*RC;*/
	/*ft_putstr(", ");*/
	/*ft_putnbr(nb_alloc_tiny);*/
	/*RC;*/
	/*if (size <= TINY)*/
		/*++nb_alloc_tiny;*/
	/*else if (size <= SMALL)*/
		/*++nb_alloc_small;*/
	/*else*/
		/*++nb_alloc_large;*/
	/*ft_putstr("nb_alloc_tiny = ");*/
	/*ft_putnbr(nb_alloc_tiny);*/
	/*RC;*/
	/*ft_putstr("nb_alloc_small = ");*/
	/*ft_putnbr(nb_alloc_small);*/
	/*RC;*/
	/*ft_putstr("nb_alloc_large = ");*/
	/*ft_putnbr(nb_alloc_large);*/
	/*RC;*/
	/*ft_putendl("Malloc");*/

	allocation_familliale = NULL;
	if (size > MAX_SIZE || size == 0)
		return (allocation_familliale);
	if (size <= SMALL)
		allocation_familliale = alloc_tiny_small(size);
	else
		allocation_familliale = alloc_large(size);

	/*DEBUG_print_allocated_zones();*/
	return (allocation_familliale);
}
