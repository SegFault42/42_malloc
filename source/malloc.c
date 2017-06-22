#include "../include/malloc.h"

t_block	*meta_tiny = NULL;
t_block	*meta_small = NULL;
void	*g_tiny_data = NULL;
void	*g_small_data = NULL;

void	free(void *addr)
{
	(void)addr;
}

bool	alloc_data(size_t size)
{
	if (size <= TINY)
	{
		g_tiny_data = mmap(NULL, TINY * 128, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		if (g_tiny_data == NULL)
		{
			ft_putstr_fd(strerror(errno), 2);
			return (false);
		}
		ft_memset(g_tiny_data, 0, TINY * 128);
	}
	else if (size <= SMALL)
	{
		g_small_data = mmap(NULL, SMALL * 128, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		if (g_small_data == NULL)
		{
			ft_putstr_fd(strerror(errno), 2);
			return (false);
		}
		ft_memset(g_small_data, 0, SMALL * 128);
	}
	return (true);
}

bool	alloc_lst(size_t size)
{
	if (size <= TINY)
	{
		meta_tiny = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		if (meta_tiny == NULL)
		{
			ft_putstr_fd(strerror(errno), 2);
			return (false);
		}
		ft_memset(meta_tiny, 0, getpagesize());
	}
	else if (size <= SMALL)
	{
		meta_small = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		if (meta_small == NULL)
		{
			ft_putstr_fd(strerror(errno), 2);
			return (false);
		}
		ft_memset(meta_small, 0, getpagesize());
	}
	return (true);
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
		/*print_hexa((unsigned int)tmp);*/
		/*ft_putstr(", ");*/
		/*ft_putnbr(0);*/
		/*RC ;*/
	++i;
	++tmp;
	while (i < NB_ZONES)
	{
		/*print_hexa((unsigned int)tmp);*/
		/*ft_putstr(", ");*/
		/*ft_putnbr(i);*/
		/*RC ;*/
		tmp_2->next = tmp;
		++tmp_2;
		init_node(tmp, flag, i);
		++tmp;
		++i;
	}
}

void	*alloc_tiny(size_t size)
{
	t_block	*tmp;

	tmp = NULL;
	ft_putstr("I'm in alloc tiny\n");
	if (size <= TINY)
	{
		if (meta_tiny == NULL)
		{
			if (alloc_lst(size) == false)
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
			if (alloc_lst(size) == false)
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

void	*malloc(size_t size)
{
		ft_putstr(CYAN"size_allocation = "END);
		ft_putnbr(size);
		RC;
	void	*allocation_familliale;
	static size_t	i = 1;
		ft_putstr("Malloc call = ");
		ft_putnbr(i);
		ft_putstr(" ");
		++i;

	allocation_familliale = NULL;
	if (size <= SMALL)
		allocation_familliale = alloc_tiny(size);

	/*t_block	*tmp = meta_tiny;*/
	/*t_block	*tmp_2 = meta_small;*/

	/*while (tmp->next && tmp->free == 1)*/
	/*{*/
		/*ft_putstr("Malloc call = ");*/
		/*ft_putnbr(i);*/
		/*ft_putstr(" , ");*/
		/*ft_putstr("size = ");*/
		/*ft_putnbr(tmp->size);*/
		/*ft_putstr(" addr tmp = ");*/
		/*print_hexa((unsigned int)tmp);*/
		/*ft_putstr(" addr tmp->ptr = ");*/
		/*print_hexa((unsigned int)tmp->ptr);*/
		/*tmp = tmp->next;*/
		/*RC ;*/
	/*}*/
	/*while (tmp_2->next && tmp_2->free == 1)*/
	/*{*/
		/*ft_putstr(" , ");*/
		/*ft_putstr("size = ");*/
		/*ft_putnbr(tmp->size);*/
		/*ft_putstr(" addr tmp = ");*/
		/*print_hexa((unsigned int)tmp);*/
		/*ft_putstr(" addr tmp->ptr = ");*/
		/*print_hexa((unsigned int)tmp->ptr);*/
		/*tmp = tmp->next;*/
		/*RC ;*/
	/*}*/
	/*RC ;*/
	/*RC ;*/
	return (allocation_familliale);
}
