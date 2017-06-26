/*#include "./include/malloc.h"*/
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>

#define RAND_TINY random = rand() % 64 + 1;
#define RAND_SMALL random = rand() % 960+ 65;
#define RAND_LARGE random = rand() % 2000 + 1025;
/*#define RAND_LARGE random = 1024;*/
#define RAND random = rand() % RAND_MAX + 1;

void	usage()
{
	write(1, "Usgae : argv[1] = size of alloc (t,s,l,r) (t for tiny, s fort small, l for large, r for random), argv[2] nb of allocation\nExample ./stress_test l 100\n", 151);
	exit(-1);
}

void	error(int argc, char **argv)
{
	if (argc != 3)
		usage();
	if (strlen(argv[1]) != 1)
		usage();
	for (int i = 0; i < strlen(argv[2]); ++i)
		if (isdigit(argv[2][i]) == 0)
			usage();
}

int	main(int argc, char **argv)
{
	error(argc, argv);
	char	*addr;
	int		random = 0;

	srand(time(NULL));
	for (int i = 0; i < atoi(argv[2]); ++i)
	{
		if (argv[1][0] == 't')
			RAND_TINY
		else if (argv[1][0] == 's')
			RAND_SMALL
		else if (argv[1][0] == 'l')
			RAND_LARGE
		else if (argv[1][0] == 'r')
			RAND
		else
			usage();
		addr = (char *)malloc(random);
		if (addr == NULL)
		{
			/*ft_putendl("addr = NULL");*/
			exit(-1);
		}
		/*else*/
			addr[0] = 42;
		/*show_alloc_mem();*/
	}
	/*show_alloc_mem();*/
}
