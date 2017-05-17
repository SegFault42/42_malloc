#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "./include/malloc.h"


int	main()
{
	char *str = malloc(sizeof(char) * -10);
	/*strcat(str, "loliiiiiiiiiiiiiiiiiiii");*/
	/*printf("%s\n", str);*/
}
