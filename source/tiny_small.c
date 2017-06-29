#include "../include/malloc.h"

extern t_memory	g_memory;

static t_block	*alloc_small(t_block *tmp, size_t size)
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
	return (tmp);
}

static t_block	*alloc_tiny(t_block *tmp, size_t size)
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
	return (tmp);
}

void	*alloc_tiny_small(size_t size)
{
	t_block	*tmp;

	tmp = NULL;
	if (size <= TINY)
	{
		if ((tmp = alloc_tiny(tmp, size)) == NULL)
			return (NULL);
	}
	else
	{
		if ((tmp = alloc_small(tmp, size)) == NULL)
			return (NULL);
	}
	while (tmp->next && tmp->free == 1)
		tmp = tmp->next;
	tmp->free = 1;
	tmp->size = size;
	return (tmp->ptr);
}

