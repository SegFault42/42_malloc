#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "./include/malloc.h"

/*Size = 1714955948*/
/*Size = 1886574843*/
/*Size = 67321540*/


int	main()
{
	char *test1 = malloc(1714955948);
	char *test2 = malloc(1886574843);
	char *test3 = malloc(67321540);
	printf("%u\n", RAND_MAX);

	show_alloc_mem();
	RC;
}

