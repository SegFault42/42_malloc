#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>

typedef struct		s_block
{
	size_t			size;		// size of allocation
	struct s_block	*next;		// next pointer
	void			*ptr;		// pointer on data
	bool			free;		// free or not
	char			data[1];	// ???
	char			flag;		// flag size (tiny, small or large)
	char			pad[5];		// variable for padding
}					t_block;

t_block	g_block = {0};
void	*node;

void	*alloc(size_t size)
{
	int i = 0;

	if (g_block.size == 15)
		return (&node[16]);
	node = mmap(0, 4096, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	return (&node[i]);
}

int	main()
{
	/*char *str;*/
	/*char *str2;*/

	/*str = (char *)alloc(15);*/
	/*g_block.size = 15;*/
	/*strcat(str, "aaaaaaaaaaaaaaa");*/
	/*printf("%s\n", str);*/
	/*str2 = (char *)alloc(15);*/
	/*strcat(str2, "2nd");*/
	/*printf("%s\n", str2);*/
	/*printf("%s\n", str);*/


	char *test;

	test = (char *)malloc(15);
	memset(test, 0, 15);
	strcat(test, "aaaaaaaaaaaaaaa");
	for (int i = 0; i < 15; ++i)
		printf("%c\n", test[i]);
	char *test2;
	test2 = (char *)malloc(15);
	memset(test2, 0, 15);
	strcat(test2, "bbbbbb");
	for (int i = 0; i < 15; ++i)
		printf("%c\n", test2[i]);
	while (1)
	{
		printf("\033[10;10H");
		for (int i = 0; i < 20000; ++i)
			printf("%c", test[i]);
		sleep(2);
		system("unset PATH");
	}
}
