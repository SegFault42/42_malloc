#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "./include/malloc.h"

/*Size = 1714955948*/
/*Size = 1886574843*/
/*Size = 67321540*/

#define M (1024 * 1024)

int	main()
{
	char *addr1 = malloc(16 * M);
	strcpy(addr1, "Bonjours\n");
	ft_putstr(addr1);

	char *addr3 = (char*)malloc(10000);
	addr3[127*M] = 42;
	/*ft_putstr(addr3);*/
	/*malloc(54 * 32);*/
	/*malloc(54 * 54);*/
	/*malloc(54 * 54 * 16);*/
	/*malloc(54 * 54 * 128);*/
	/*show_alloc_mem();*/
	return (0);
}

