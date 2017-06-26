#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "./include/malloc.h"


int	main()
{
	char *test1 = malloc(18446744073709551615UL /100000);

	show_alloc_mem();
	RC;
}

