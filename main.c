#include <stdio.h>
#include <string.h>
#include <unistd.h>
/*#include <stdlib.h>*/
#include "./include/malloc.h"

/*Size = 1714955948*/
/*Size = 1886574843*/
/*Size = 67321540*/

/*#define M (1024 * 1024)*/

int	main()
{
	malloc(4096);
	malloc(4096);
	malloc(4096);
	malloc(4096);
	show_alloc_mem();
	return (0);
}

