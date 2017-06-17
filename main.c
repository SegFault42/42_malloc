#include <stdio.h>
#include <string.h>
/*#include <stdlib.h>*/
#include <unistd.h>
#include "./include/malloc.h"

#define SIZE 125

int	main()
{

	char *test1 = (char *)malloc(sizeof(char) * 1101);
	char *test2 = (char *)malloc(sizeof(char) * 1102);
	char *test3 = (char *)malloc(sizeof(char) * 1103);
	char *test4 = (char *)malloc(sizeof(char) * 1104);
	char *test5 = (char *)malloc(sizeof(char) * 1105);
	free(test1);
	free(test2);
	free(test3);
	free(test4);
	char *test6 = (char *)malloc(sizeof(char) * 1106);
	char *test7 = (char *)malloc(sizeof(char) * 1107);
	char *test8 = (char *)malloc(sizeof(char) * 1108);
	char *test9 = (char *)malloc(sizeof(char) * 1109);
	char *test10 = (char *)malloc(sizeof(char) * 1110);
	free(test5);
	free(test6);
	free(test7);
	free(test8);
	free(test9);
	free(test10);
	show_alloc_mem();
}

