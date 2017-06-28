#include <stdio.h>
#include <string.h>
#include <unistd.h>
/*#include <stdlib.h>*/
#include "./include/malloc.h"

/*Size = 1714955948*/
/*Size = 1886574843*/
/*Size = 67321540*/

#define M (1024 * 1024)
	void print(char *s)
	{
	write(1, s, strlen(s));
	}

int	main()
{
	/*char *str = (char *)malloc(20000);*/
	/*memset(str, 'a', 20000);*/
	/*printf("str (1) = %p - %s\n", str, str);*/
	/*str = realloc(str, 10);*/
	/*printf("str (2) = %p - %s\n", str, str);*/
	/*show_alloc_mem();*/

	/*char *str1 = (char *)malloc(3312);*/
	/*memset(str1, 'a', 3312);*/
	/*printf("str1 (1) = %p - %s\n", str1, str1);*/
	/*str1 = realloc(str1, 30000);*/
	/*printf("str1 (2) = %p - %s\n", str1, str1);*/

char *addr1;
char *addr3;

addr1 = (char*)malloc(16*M);
strcpy(addr1, "Bonjours\n");
print(addr1);
addr3 = (char*)realloc(addr1, 128*M);
addr3[127*M] = 42;
print(addr3);
	return (0);
}

