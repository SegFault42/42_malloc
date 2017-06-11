#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "./include/malloc.h"
#include "./libft/includes/libft.h"
#include <limits.h>

#define SIZE 125

int	main()
{
	char *str = malloc(sizeof(char) * 1);
	/*char *str1 = malloc(sizeof(char) * 56);*/
	/*char *str2 = malloc(sizeof(char) * 1);*/
	if (str == NULL)
	{
		/*printf("NULL\n");*/
		return ((int)NULL);
	}
	for (int i = 0; i < SIZE; ++i)
		strcat(str, "lllllllllllllaaaaaaaaaaaaaaaaaaaaaaallllllllllllllllll");
	write(1, str, strlen(str));
	write(1, "\n", 1);
	/*show_alloc_mem();*/
}

/*int	main(int argc, char **argv)*/
/*{*/
	/*int	size = atoi(argv[1]) + 32;*/
	/*int	modulo = (size + 32) % 16;*/

	/*if (modulo != 0)*/
	/*{*/
		/*size += 16 - modulo;*/
	/*}*/
	/*size *= 128;*/
	/*printf("size = %d\n%d %% 16 = %d\n", size, size, size % 16);*/
	/*printf("size = %d %% 4096 = %d\n", size, size % 4096);*/
/*}*/

