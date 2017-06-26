#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "./include/malloc.h"


int	main()
{
	char *test1 = malloc(1001);
	char *test2 = malloc(1002);
	char *test3 = malloc(1003);
	char *test4 = malloc(1004);
	char *test5 = malloc(1005);
	char *test6 = malloc(1006);
	free(test1);

	show_alloc_mem();
	RC;
}

