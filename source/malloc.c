#include "../include/malloc.h"

t_block	*g_block = NULL;
t_ctrl	*ctrl = NULL;

/*void	*realloc(void *ptr, size_t size)*/
/*{*/
	/*(void)size;*/
	/*return (ptr);*/
/*}*/

void	free(void *addr)
{
	ft_putendl("free function");
	ft_putstr(GREEN"");
	print_hexa((unsigned long)addr);
	RC;
	t_block	*tmp;

	tmp = g_block;
	ft_putstr(PINK"");
	print_hexa((unsigned long)tmp);
	while (tmp)
	{
		/*RC;*/
		/*ft_putstr(YELLOW"");*/
		/*print_hexa((unsigned long)tmp->ptr);*/
		/*RC;*/
		if (tmp->ptr == addr)
		{
			/*ft_putstr(YELLOW"");*/
			/*print_hexa((unsigned long)tmp->ptr);*/
			/*ft_putendl("tmp->ptr = addr");*/
			tmp->free = 0;
			/*tmp->ptr = NULL;*/
			tmp->size = 0;
			tmp->flag = 0;
			break ;
		}
		tmp = tmp->next;
		/*ft_putendl("next");*/
	}
	ft_putendl(END"");
	(void)addr;
}

void	setup_node(size_t size, t_block *node)
{
	if (size <= TINY)
	{
		node->ptr = mmap(0, TINY, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		node->flag = 't';
	}
	else if (size <= SMALL)
	{
		node->ptr = mmap(0, SMALL, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		node->flag = 's';
	}
	else
	{
		node->flag = 'l';
		node->ptr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	}
	if (node->ptr == MAP_FAILED)
	{
		ft_putstr_fd("MMAP FAILED TO ALLOCATE PTR : ",2);
		ft_putendl_fd(strerror(errno),2);
		exit (-1);
	}
	if (size <= TINY)
		ft_memset(node->ptr, 0, TINY);
	else if (size <= SMALL)
		ft_memset(node->ptr, 0, SMALL);
	else
		ft_memset(node->ptr, 0, size);
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
		setup_node(size, g_block);
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = create_node();
		setup_node(size, tmp);
	}
}

bool	check_list_filled()
{
	t_block	*tmp;

	tmp = g_block;
	while (tmp->next && tmp->free == 1)
		tmp = tmp->next;
	if (tmp->next == NULL)
		return (LST_FULL);
	return (LST_NOT_FULL);
}

void	*alloc_tiny_small(size_t size)
{
	t_block	*tmp;
	int i = 0;

	if (g_block == NULL || check_list_filled() == LST_FULL)
	{
		while (i < 128)
		{
			lst_push_back(size);
			++i;
		}
	}
	/*else*/
		/*lst_push_back(size);*/
	tmp = g_block;
	while (tmp->next && tmp->free == 1)
		tmp = tmp->next;
	tmp->free = 1;
	tmp->size = size;
	if (size <= TINY)
		tmp->flag = 't';
	else if (size <= SMALL)
		tmp->flag = 's';
	else
		tmp->flag = 'l';
	return (tmp->ptr);
}

void	DEBUG_print_node(t_block *node, int i)
{
	ft_putstr(ORANGE"Node ");
	ft_putnbr(i);
	ft_putendl(" :");

	ft_putstr(CYAN"size = ");
	ft_putnbr(node->size);
	ft_putendl("");

	ft_putstr(PURPLE"ptr = ");
	if (node->ptr)
		ft_putendl("NOT NULL");
	else
		ft_putendl("NULL");
	
	ft_putstr(YELLOW"free = ");
	ft_putnbr(node->free);
	ft_putendl("");

	ft_putstr(GREY"flag = ");
	if (node->flag == 't')
		ft_putendl("TINY");
	else if (node->flag == 's')
		ft_putendl("SMALL");
	else
		ft_putendl("LARGE");

	ft_putstr(PINK"next = ");
	if (node->next)
		ft_putendl("NOT NULL");
	else
		ft_putendl("NULL");

	ft_putendl(""END);
	
}

void	*malloc(size_t size)
{
	t_block	*tmp;
	void	*alloc = NULL;
	int i = 1;

	/*if (size <= SMALL)*/
		alloc = alloc_tiny_small(size);
	/*else*/
		/*return (alloc_large(size));*/
	if (g_block == NULL)
		ft_putendl("NULL");
	tmp = g_block;
	ft_putendl(RED"============================================================="END);
	while (tmp && tmp->free == 1)
	{
		DEBUG_print_node(tmp, i);
		tmp = tmp->next;
		++i;
	}
	return (alloc);
 }
