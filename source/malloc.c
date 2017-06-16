#include "../include/malloc.h"

t_block	*g_tiny = NULL;
t_block	*g_small = NULL;
t_block	*g_large = NULL;

/*void	*realloc(void *ptr, size_t size)*/
/*{*/
	/*(void)size;*/
	/*return (ptr);*/
/*}*/

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
	}
	return (total);
}

void	show_alloc_mem()
{
	t_block	*tmp_tiny;
	size_t	total;

	tmp_tiny = g_tiny;
	total = 0;
	if (g_tiny)
	{
		ft_putstr("TINY : ");
		print_hexa((unsigned int)g_tiny);
		RC;
		total += print_data_mem(g_tiny);
	}
	if (g_small)
	{
		ft_putstr("SMALL : ");
		print_hexa((unsigned int)g_small);
		RC;
		total += print_data_mem(g_small);
	}
	if (g_large)
	{
		ft_putstr("LARGE : ");
		print_hexa((unsigned int)g_large);
		RC;
		total += print_data_mem(g_large);
	}
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putendl(" octets");
}

bool	look_for_addr(t_block *block, void *addr)
{
	t_block	*tmp;
	size_t	DEBUG_i = 1;

	tmp = block;
	while (tmp)
	{
		/*RC;*/
		DEBUG_free_current_addr(tmp->ptr, DEBUG_i);
		if (tmp->ptr == addr)
		{
			/*ft_putstr(YELLOW"");*/
			/*print_hexa((unsigned long)tmp->ptr);*/
			/*ft_putendl("tmp->ptr = addr");*/
			tmp->free = 0;
			/*tmp->ptr = NULL;*/
			tmp->size = 0;
			tmp->flag = 0;
			return (true);
		}
		tmp = tmp->next;
		/*ft_putendl("next");*/
		++DEBUG_i;
	}
	return (false);
}

void	free_large(void *addr)
{
	t_block	*tmp;
	size_t	DEBUG_i = 1;

	tmp = g_large;
	while (tmp)
	{
		/*RC;*/
		DEBUG_free_current_addr(tmp->ptr, DEBUG_i);
		if (tmp->ptr == addr)
		{
			/*ft_putstr(YELLOW"");*/
			/*print_hexa((unsigned long)tmp->ptr);*/
			/*ft_putendl("tmp->ptr = addr");*/
			if (munmap(tmp->ptr, tmp->size) != 0)
			{
				ft_putstr_fd("munmap error : ", 2);
				ft_putendl_fd(strerror(errno), 2);
			}
			tmp->free = 0;
			/*tmp->ptr = NULL;*/
			tmp->size = 0;
			tmp->flag = 0;
			return ;
		}
		tmp = tmp->next;
		/*ft_putendl("next");*/
		++DEBUG_i;
	}
	
}

void	free(void *addr)
{
	DEBUG_calling_free_message();
	DEBUG_address_to_free(addr);
	if (look_for_addr(g_tiny, addr) == true)
		return ;
	else if (look_for_addr(g_small, addr) == true)
		return ;
	else
		free_large(addr);
	if (DEBUG_ADDRESS_TO_FREE == 1)
		ft_putendl(END"");
}

bool	alloc_ptr_node(size_t size, t_block *node)
{
	if (size <= TINY)
		node->ptr = mmap(0, TINY, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	else if (size <= SMALL)
		node->ptr = mmap(0, SMALL, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	else
		node->ptr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (node->ptr == MAP_FAILED)
	{
		DEBUG_show_ret_mmap((int)node->ptr);
		ft_putstr_fd("MMAP FAILED TO ALLOCATE PTR : ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (false);
	}
	if (size <= TINY)
		ft_memset(node->ptr, 0, TINY);
	else if (size <= SMALL)
		ft_memset(node->ptr, 0, SMALL);
	else
		ft_memset(node->ptr, 0, size);
	return (true);
}

void	*create_node()
{
	t_block *tmp;

	tmp = mmap(0, sizeof(t_block), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (tmp == MAP_FAILED)
	{
		DEBUG_show_ret_mmap((int)tmp->ptr);
		ft_putstr_fd("MMAP FAILED TO ALLOCATE NEW NODE : ",2);
		/*ft_putendl_fd(strerror(errno),2);*/
		return (NULL);
	}
	ft_memset(tmp, 0, sizeof(t_block));
	return (tmp);
}

bool	lst_push_back(size_t size)
{
	t_block	*tmp;

	tmp = NULL;
	if (size <= TINY)
		tmp = g_tiny;
	else if (size <= SMALL)
		tmp = g_small;
	else
		tmp = g_large;
	if (tmp == NULL)
	{
		if (size <= TINY)
		{
			if ((g_tiny = create_node()) == NULL)
				return (false);
			if ((alloc_ptr_node(size, g_tiny)) == false)
				return (false);
		}
		else if (size <= SMALL)
		{
			if ((g_small = create_node()) == NULL)
				return (false);
			if ((alloc_ptr_node(size, g_small)) == false)
				return (false);
		}
		else
		{
			if ((g_large = create_node()) == NULL)
				return (false);
			if ((alloc_ptr_node(size, g_large)) == false)
				return (false);
		}
		/*DEBUG_print_node(tmp, 1);*/
		/*sleep(3);*/
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		if ((tmp->next = create_node()) == NULL)
			return (false);
		if ((alloc_ptr_node(size, tmp->next)) == false)
			return (false);
	}
	return (true);
}

bool	check_list_filled(size_t size)
{
	t_block	*tmp;

	tmp = NULL;
	if (size <= TINY)
		tmp = g_tiny;
	else if (size <= SMALL)
		tmp = g_small;
	while (tmp->next && tmp->free == 1)
		tmp = tmp->next;
	if (tmp->next == NULL)
		return (LST_FULL);
	return (LST_NOT_FULL);
}

void	*init_node(size_t size)
{
	t_block	*tmp;

	tmp = NULL;
	if (size <= TINY)
		tmp = g_tiny;
	else if (size <= SMALL)
		tmp = g_small;
	else
		tmp = g_large;
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

void	*alloc_tiny_small(size_t size)
{
	int i = 0;

	if (size <= TINY)
	{
		if (g_tiny == NULL || check_list_filled(size) == LST_FULL)
			while (i < NB_ZONES)
			{
				if (lst_push_back(size) == false)
					return (NULL);
				++i;
			}
	}
	else if (size <= SMALL)
	{
		if (g_small == NULL || check_list_filled(size) == LST_FULL)
			while (i < NB_ZONES)
			{
				if (lst_push_back(size) == false)
					return (NULL);
				++i;
			}
	}
	return (init_node(size));
}

void	*alloc_large(size_t size)
{
	if (lst_push_back(size) == false)
		return (NULL);
	return (init_node(size));
}

void	*malloc(size_t size)
{
	void	*alloc = NULL;
	size_t DEBUG_iter_malloc_call = 1;

	DEBUG_calling_malloc();
	if (size <= SMALL)
		alloc = alloc_tiny_small(size);
	else
		alloc = alloc_large(size);
	DEBUG_print_info_node(DEBUG_iter_malloc_call);
	return (alloc);
 }
