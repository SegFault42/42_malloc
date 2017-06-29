#include "../include/malloc.h"

extern t_memory	g_memory;

bool	alloc_data(size_t size)
{
	if (size <= TINY)
	{
		g_memory.tiny_data = mmap(NULL, TINY * 128, PROT, FLAG, -1, 0);
		if (g_memory.tiny_data == NULL)
			return (false);
	}
	else if (size <= SMALL)
	{
		g_memory.small_data = mmap(NULL, SMALL * 128, PROT, FLAG, -1, 0);
		if (g_memory.small_data == NULL)
			return (false);
	}
	else
	{
		g_memory.large_data = mmap(NULL, size, PROT, FLAG, -1, 0);
		if (g_memory.large_data == NULL)
			return (false);
	}
	return (true);
}

t_block	*alloc_meta()
{
	t_block	*tmp;

	tmp = mmap(NULL, getpagesize(), PROT, FLAG, -1, 0);
	if (tmp == NULL)
		return (NULL);
	ft_memset(tmp, 0, getpagesize());
	return (tmp);
}


