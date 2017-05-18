#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "./include/malloc.h"


int	main()
{
	char *str = malloc(sizeof(char) * 1000000);
	if (str == NULL)
	{
		printf("NULL\n");
		return ((int)NULL);
	}
	/*strcat(str, "loliiiiiiiiiiiiiiiiiiii");*/
	/*printf("%s\n", str);*/
}
