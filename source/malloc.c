#include "../include/malloc.h"

t_memory	g_memory = {NULL, NULL, NULL, NULL, NULL, NULL};
t_mutex		g_mutex = {};

void	*calloc(size_t nmemb, size_t size)
{
	void	*allocation_familliale;

	if (pthread_mutex_lock(&g_mutex.m_calloc) == EINVAL)
	{
		pthread_mutex_init(&g_mutex.m_calloc, NULL);
		pthread_mutex_lock(&g_mutex.m_calloc);
	}
	if (size > MAX_SIZE || size == 0 || nmemb == 0)
		allocation_familliale = NULL;
	else
	{
		allocation_familliale = malloc(nmemb * size);
		ft_memset(allocation_familliale, 0, nmemb * size);
	}
	pthread_mutex_unlock(&g_mutex.m_calloc);
	return (allocation_familliale);
}

void	*malloc(size_t size)
{
	void	*allocation_familliale;

	allocation_familliale = NULL;
	if (pthread_mutex_lock(&g_mutex.m_malloc) == EINVAL)
	{
		pthread_mutex_init(&g_mutex.m_malloc, NULL);
		pthread_mutex_lock(&g_mutex.m_malloc);
	}
	if (size > MAX_SIZE || size == 0)
		allocation_familliale = alloc_tiny_small(size);
	else if (size <= SMALL)
		allocation_familliale = alloc_tiny_small(size);
	else
		allocation_familliale = alloc_large(size);
	debug_env(size, allocation_familliale);
	pthread_mutex_unlock(&g_mutex.m_malloc);
	return (allocation_familliale);
}
