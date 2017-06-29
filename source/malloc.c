#include "../include/malloc.h"

t_memory	g_memory = {NULL, NULL, NULL, NULL, NULL, NULL};

void	*calloc(size_t nmemb, size_t size)
{
	void	*allocation_familliale;

	allocation_familliale = NULL;
	if (size > MAX_SIZE || size == 0 || nmemb == 0)
		return (allocation_familliale);
	allocation_familliale = malloc(nmemb * size);
	ft_memset(allocation_familliale, 0, nmemb * size);
	return (allocation_familliale);
}

void	*malloc(size_t size)
{
	void	*allocation_familliale;

	allocation_familliale = NULL;
	if (size > MAX_SIZE || size == 0)
		return (allocation_familliale);
	if (size <= SMALL)
		allocation_familliale = alloc_tiny_small(size);
	else
		allocation_familliale = alloc_large(size);
	/*DEBUG_print_allocated_zones();*/
	/*ft_putstr("Exit");*/
	debug_env(size, allocation_familliale);
	return (allocation_familliale);
}
