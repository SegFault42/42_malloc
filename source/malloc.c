#include "../include/malloc.h"

t_block	*g_block = NULL;
t_ctrl	*ctrl = NULL;

void	free(void	*addr)
{
	(void)addr;
}

void	setup_node(size_t size, t_block *node)
{
	if (size <= TINY)
		node->ptr = mmap(0, TINY, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	else if (size <= SMALL)
		node->ptr = mmap(0, SMALL, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (node->ptr == MAP_FAILED)
	{
		ft_putstr_fd("MMAP FAILED TO ALLOCATE PTR : ",2);
		ft_putendl_fd(strerror(errno),2);
		exit (-1);
	}
	node->size = 0;
}

void	*create_node()
{
	t_block *tmp;

	tmp = mmap(0, sizeof(t_block), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (tmp == MAP_FAILED)
	{
		ft_putstr_fd("MMAP FAILED TO ALLOCATE NEW NODE : ",2);
		ft_putendl_fd(strerror(errno),2);
		exit (-1);
	}
	memset(tmp, 0, sizeof(t_block));
	tmp->next = NULL;
	return (tmp);
}

void	lst_push_back(size_t size)
{
	t_block	*tmp;

	tmp = g_block;
	if (tmp == NULL)
	{
		g_block = create_node();
		ft_putstr(CYAN"first node created\n"END);
		setup_node(size, g_block);
	}
	else
	{
		while (tmp->next)
		{
			ft_putstr("a");
			tmp = tmp->next;
		}
		ft_putendl("");
		tmp->next = create_node();
		setup_node(size, tmp);
	}
}

void	*alloc_tiny_small(size_t size)
{
	t_block	*tmp;
	int i = 0;

	if (g_block == NULL)
	{
		while (i < 128)
		{
			lst_push_back(size);
			++i;
			ft_putnbr(i);
		}
	}
	/*else*/
		/*lst_push_back(size);*/
	tmp = g_block;
	while (tmp->next && tmp->free == 1)
		tmp = tmp->next;
	tmp->free = 1;
	tmp->size = size;
	return (tmp->ptr);
}

void	*malloc(size_t size)
{
	t_block	*tmp;
	void	*alloc = NULL;
	int i = 1;

	if (size <= SMALL)
		alloc = alloc_tiny_small(size);
	/*else*/
		/*return (alloc_large(size));*/
	if (g_block == NULL)
		ft_putendl("NULL");
	tmp = g_block;
	ft_putendl(RED"============================================================="END);
	while (tmp->next && tmp->free == 1)
	{
		ft_putstr("node ");
		ft_putnbr(i);
		ft_putstr(" = ");
		ft_putnbr(tmp->size);
		ft_putendl("");
		tmp = tmp->next;
		++i;
	}
	return (alloc);
 }
