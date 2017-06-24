#include "./include/malloc.h"
#include <time.h>
#include <stdlib.h>
/*#include <unistd.h>*/

#define RAND_TINY random = rand() % 64 + 1;
#define RAND_SMALL random = rand() % 192 + 65;
#define RAND_LARGE random = rand() % RAND_MAX + 257;

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		write(1, "number allocation missing ! (in param)\n", 39);
		return (-1);
	}

	char	*addr;

	srand(time(NULL));
	int	random = 0;
	for (int i = 0; i < atoi(argv[1]); ++i)
	{
		RAND_SMALL
		addr = (char *)malloc(random);
	}
	show_alloc_mem();
}
