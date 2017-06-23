#include "../include/malloc.h"

t_block	*meta_tiny = NULL;
t_block	*meta_small = NULL;
t_block	*meta_large = NULL;
void	*g_tiny_data = NULL;
void	*g_small_data = NULL;
void	*g_large_data = NULL;

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
		tmp_2 = meta_tiny;
	}
	else if (flag == 's')
	{
		tmp = meta_small;
		tmp_2 = meta_small;
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

void	fill_lst_large()
{
	t_block	*tmp;
	t_block	*tmp_2;

	size_t	i;

	i = 1;
	tmp = meta_large;
	tmp_2 = meta_large;
	if (meta_large == NULL)
	{
		tmp->ptr = g_large_data;
		tmp->flag = 'l';
	}
	else
	{
		while (tmp->next && tmp->free == 1)
		{
			tmp = tmp->next;
			++i;
		}
		tmp_2 += i;
		tmp->next = tmp_2;
		tmp_2->ptr = g_large_data;
		tmp_2->flag = 'l';
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
		tmp = meta_small;
	}
	while (tmp->next && tmp->free == 1)
		tmp = tmp->next;
	tmp->free = 1;
	tmp->size = size;
	return (tmp->ptr);
}


void	*alloc_large(size_t size)
{
	t_block	*tmp;

	tmp = meta_large;
	if (meta_large == NULL)
	{
		if ((meta_large = alloc_meta()) == NULL)
			return (NULL);
		if (alloc_data(size) == false)
			return (NULL);
		fill_lst_large();
	}
	while (tmp->next && tmp->free == 1)
		tmp = tmp->next;
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
