#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>

typedef struct		s_test
{
	struct s_test	*next;
	size_t			size;
	void			*ptr;
	bool			free;
	char			flag;
	char			pad[6];
}					t_test;

void	init_node(size_t size, t_test *node)
{
	node->size = size;
	node->free = 1;
	node->next = NULL;
}

int	main()
{
	t_test	*page = mmap(0, 4096, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);

	t_test	*node = page;
	t_test	*tmp = node;
	init_node(0, node);
	printf("%d, %p\n", 0, node);
	++node;
	for (int i = 1; i < 128; ++i)
	{
		tmp->next = node;
		init_node(i, node);
		printf("%d, %p\n", i, node);
		++node;
		++tmp;
	}
	printf("lol\n");
	t_test *tmp_2 = page;
	while (tmp_2)
	{
		printf("%zu ", tmp_2->size);
		printf("%p\n", tmp_2);
		tmp_2 = tmp_2->next;
	}
}
