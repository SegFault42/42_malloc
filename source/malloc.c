#include "../include/malloc.h"

t_block	*meta_tiny = NULL;
t_block	*meta_small = NULL;
t_block	*meta_large = NULL;
void	*g_tiny_data = NULL;
void	*g_small_data = NULL;
void	*g_large_data = NULL;

bool	check_if_meta_full(size_t size)
{
	t_block	*tmp;

	if (size <= TINY)
		tmp = meta_tiny;
	else
		tmp = meta_small;
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
	return (total);
}

void	show_alloc_mem()
{
	size_t	total;

	total = 0;
	if (meta_tiny && meta_tiny->free == 1)
	{
		ft_putstr("TINY : ");
		print_hexa((unsigned int)meta_tiny);
		RC;
		total += print_data_mem(meta_tiny);
	}
	if (meta_small && meta_small->free == 1)
	{
		ft_putstr("SMALL : ");
		print_hexa((unsigned int)meta_small);
		RC;
		total += print_data_mem(meta_small);
	}
	if (meta_large && meta_large->free == 1)
	{
		ft_putstr("LARGE : ");
		print_hexa((unsigned int)meta_large);
		RC;
		total += print_data_mem(meta_large);
	}
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putendl(" octets");
}

void	free(void *addr)
{
	(void)addr;
}

bool	alloc_data(size_t size)
{
	if (size <= TINY)
	{
		g_tiny_data = mmap(NULL, TINY * 128, PROT, FLAG, -1, 0);
		if (g_tiny_data == NULL)
		{
			ft_putstr_fd(strerror(errno), 2);
			return (false);
		}
		ft_memset(g_tiny_data, 0, TINY * 128);
	}
	else if (size <= SMALL)
	{
		g_small_data = mmap(NULL, SMALL * 128, PROT, FLAG, -1, 0);
		if (g_small_data == NULL)
		{
			ft_putstr_fd(strerror(errno), 2);
			return (false);
		}
		ft_memset(g_small_data, 0, SMALL * 128);
	}
	else
	{
		g_large_data = mmap(NULL, size, PROT, FLAG, -1, 0);
		if (g_large_data == NULL)
		{
			ft_putstr_fd(strerror(errno), 2);
			return (false);
		}
		ft_memset(g_large_data, 0, size);
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
		tmp = g_tiny_data;
		tmp += i * TINY;
	}
	else if (flag == 's')
	{
		tmp = g_small_data;
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
		tmp = meta_tiny;
		while (tmp->next)
			tmp = tmp->next;
		tmp_2 = tmp;
	}
	else if (flag == 's')
	{
		tmp = meta_small;
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
		if (meta_tiny == NULL)
		{
			if ((meta_tiny = alloc_meta()) == NULL)
				return (NULL);
			if (alloc_data(size) == false)
				return (NULL);
			fill_lst('t');
		}
		else if (check_if_meta_full(size) == LST_FULL)
		{
			tmp = meta_tiny;
			while (tmp->next)
				tmp = tmp->next;
			if ((tmp->next = alloc_meta()) == NULL)
				return (NULL);
			if (alloc_data(size) == false)
				return (NULL);
			fill_lst('t');
		}
		tmp = meta_tiny;
	}
	else if (size <= SMALL)
	{
		if (meta_small == NULL)
		{
			if ((meta_small = alloc_meta()) == NULL)
				return (NULL);
			if (alloc_data(size) == false)
				return (NULL);
			fill_lst('s');
		}
		else if (check_if_meta_full(size) == LST_FULL)
		{
			tmp = meta_small;
			while (tmp->next)
				tmp = tmp->next;
			if ((tmp->next = alloc_meta()) == NULL)
				return (NULL);
			if (alloc_data(size) == false)
				return (NULL);
			fill_lst('s');
		}
		tmp = meta_small;
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
	tmp = meta_large;
	tmp_2 = meta_large;
	while (tmp->next && tmp->free == 1)
	{
		tmp = tmp->next;
		++i;
	}
	tmp_2 += i;
	tmp->next = tmp_2;
	tmp->ptr = g_large_data + ptr;
	tmp->flag = 'l';
	/*if (tmp_2)*/
		/*tmp_2->next = NULL;*/
}

size_t	check_if_alloc_fill(size_t size)
{
	t_block	*tmp;
	size_t	begin_page;
	size_t	i;
	size_t	size_alloc_in_page;

	begin_page = 1;
	i = 1;
	tmp = meta_large;
	size_alloc_in_page = 0;
	while (tmp->next && tmp->free == 1)
	{
		if ((int)tmp->ptr % getpagesize() == 0)
			begin_page = i;
		++i;
		tmp = tmp->next;
	}
		ft_putendl("a");
	tmp = meta_large;
	i = 1;
	while (i < begin_page)
	{
		tmp = tmp->next;
		++i;
	}
	while (tmp->next && tmp->free == 1)
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

	tmp = meta_large;
	addr_ok = 0;
	if (meta_large == NULL)
	{
		if ((meta_large = alloc_meta()) == NULL)
			return (NULL);
		if (alloc_data(size) == false)
			return (NULL);
		fill_lst_large(0);
		tmp = meta_large;
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
		while (tmp->next && tmp->free == 1)
		{
			tmp = tmp->next;
			/*print_hexa((unsigned int )tmp);*/
			/*RC;*/
		}
	tmp->free = 1;
	tmp->size = size;
	return (tmp->ptr);
}

void	*malloc(size_t size)
{
	void	*allocation_familliale;

	allocation_familliale = NULL;
	if (size <= SMALL)
		allocation_familliale = alloc_tiny_small(size);
	else
		allocation_familliale = alloc_large(size);

	DEBUG_print_allocated_zones();
	return (allocation_familliale);
}
