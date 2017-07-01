#include "../include/malloc.h"

extern t_memory	g_memory;

static void	fill_lst_large(size_t ptr)
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
		while (tmp)
			tmp = tmp->next;
		if (!tmp)
			return ;
		tmp->next = alloc_meta();
	}
	tmp_2 += i;
	tmp->next = tmp_2;
	tmp->ptr = g_memory.large_data + ptr;
	tmp->flag = 'l';
	if (tmp_2)
		tmp_2->next = NULL;
}

/*static size_t	check_if_alloc_fill(size_t size)*/
/*{*/
	/*t_block	*tmp;*/
	/*size_t	begin_page;*/
	/*size_t	i;*/

	/*begin_page = 1;*/
	/*i = 1;*/
	/*tmp = g_memory.meta_large;*/
	/*while (tmp && tmp->free == 1)*/
	/*{*/
		/*if ((int)tmp->ptr % getpagesize() == 0)*/
			/*begin_page = i;*/
		/*++i;*/
		/*tmp = tmp->next;*/
	/*}*/
	/*tmp = g_memory.meta_large;*/
	/*tmp += begin_page;*/
	/*i = 0;*/
	/*while (tmp && tmp->free == 1)*/
	/*{*/
		/*i += tmp->size;*/
		/*tmp = tmp->next;*/
	/*}*/
	/*if (getpagesize() - i >= size)*/
		/*return (i);*/
	/*return (0);*/
/*}*/

static t_block	*allocation(t_block *tmp, size_t size)
{
	/*size_t	addr_ok;*/

	if (g_memory.meta_large == NULL)
	{
		if ((g_memory.meta_large = alloc_meta()) == NULL)
			return (NULL);
	}
	if (alloc_data(size) == false)
		return (NULL);
	fill_lst_large(0);
	tmp = g_memory.meta_large;
	/*}*/
	/*else*/
	/*{*/
		/*if ((addr_ok = check_if_alloc_fill(size)) == 0)*/
		/*{*/
			/*if (alloc_data(size) == false)*/
				/*return (NULL);*/
			/*fill_lst_large(0);*/
		/*}*/
		/*else*/
			/*fill_lst_large(addr_ok);*/
	/*}*/
	return (tmp);
}

void	*alloc_large(size_t size)
{
	t_block	*tmp;

	tmp = g_memory.meta_large;
	if ((tmp = allocation(tmp, size)) == NULL)
		return (NULL);
	tmp = g_memory.meta_large;
	while (tmp && tmp->free == 1)
		tmp = tmp->next;
	if (!tmp)
	{
		if (alloc_data(size) == false)
			return (NULL);
		fill_lst_large(0);
		tmp = g_memory.meta_large;
	}
	tmp->free = 1;
	tmp->size = size;
	return (tmp->ptr);
}

