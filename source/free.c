#include "../include/malloc.h"

extern t_memory	g_memory;
extern t_mutex	g_mutex;

static bool	look_for_addr(void *addr)
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

static void	free_large(void *addr)
{
	t_block	*tmp;

	tmp = g_memory.meta_large;
	while (tmp)
	{
		if (tmp->ptr == addr)
		{
			if (munmap(tmp->ptr, tmp->size) != -1)
			{
				tmp->free = 0;
				tmp->ptr = NULL;
				tmp->size = 0;
				tmp->flag = 0;
			}
			return ;
		}
		tmp = tmp->next;
	}
}

void	free(void *addr)
{
	if (pthread_mutex_lock(&g_mutex.m_free) == EINVAL)
	{
		pthread_mutex_init(&g_mutex.m_free, NULL);
		pthread_mutex_lock(&g_mutex.m_free);
	}
	if (addr == NULL || look_for_addr(addr) == true)
	{
		pthread_mutex_unlock(&g_mutex.m_free);
		return ;
	}
	else
		free_large(addr);
	pthread_mutex_unlock(&g_mutex.m_free);
}

