#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "./include/malloc.h"
#include "./libft/includes/libft.h"
#include <limits.h>

int	main()
{
	char *str = malloc(sizeof(char) * 28);
	char *str1 = malloc(sizeof(char) * 56);
	char *str2 = malloc(sizeof(char) * 1);
	if (str == NULL)
	{
		/*printf("NULL\n");*/
		return ((int)NULL);
	}
	/*strcat(str, "loliiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii\n");*/
	write(1, str, strlen(str));
	show_alloc_mem();
}
