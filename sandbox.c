#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>

void	free(void *lol)
{
	(void)lol;
}

void	*malloc(size_t size)
{
	static char i = 'a';

	write(1, &i, 1);
	write(1, "\n", 1);
	++i;
	void *node = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	return (node);
}

