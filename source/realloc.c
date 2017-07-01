#include "../include/malloc.h"

#define IF_TINY (size <= TINY && tmp_meta->size <= TINY)
#define IF_SMALL (size <= SMALL && tmp_meta->size <= SMALL)
#define IF_FILL (size <= tmp_meta->size + (tmp_meta->size % getpagesize())\
&& size > SMALL)

extern t_memory	g_memory;
extern t_mutex	g_mutex;

static t_block	*look_for_ptr(void *ptr)
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

t_block	*error(void *ptr, size_t size)
{
	t_block	*tmp_meta;

	if (size == 0 && ptr)
	{
		free(ptr);
		return (NULL);
	}
	tmp_meta = look_for_ptr(ptr);
	if (tmp_meta == NULL)
		return (NULL);
	return (tmp_meta);
}

void	*reallocation(void *ptr, size_t size)
{
	t_block	*tmp_meta;
	void	*allocation_familliale;

	if (ptr == NULL)
		return (malloc(size));
	else if ((tmp_meta = error(ptr, size)) == NULL)
		return (NULL);
	else if (IF_TINY || IF_SMALL || IF_FILL)
		return (ptr);
	else
	{
		allocation_familliale = malloc(size);
		if (allocation_familliale)
		{
			if (size < tmp_meta->size)
				ft_memcpy(allocation_familliale, ptr, size);
			else
				ft_memcpy(allocation_familliale, ptr, tmp_meta->size);
		}
		free(ptr);
	}
	return (allocation_familliale);
}

void	*realloc(void *ptr, size_t size)
{
	void	*allocation_familliale;

	if (pthread_mutex_lock(&g_mutex.m_realloc) == EINVAL)
	{
		pthread_mutex_init(&g_mutex.m_realloc, NULL);
		pthread_mutex_lock(&g_mutex.m_realloc);
	}
	allocation_familliale = reallocation(ptr, size);
	pthread_mutex_unlock(&g_mutex.m_realloc);
	return (allocation_familliale);
}
