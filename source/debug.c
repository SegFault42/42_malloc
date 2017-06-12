#include "../include/malloc.h"

extern t_block	*g_block;

void	DEBUG_calling_malloc()
{
	static size_t iter = 1;

	ft_putstr(WHITE"Calling malloc ");
	ft_putnbr(iter);
	ft_putstr(" time\n"END);
	++iter;
}

void	DEBUG_print_node(t_block *node, int i)
{
	ft_putstr(ORANGE"Node ");
	ft_putnbr(i);
	ft_putendl(" :");

	ft_putstr(CYAN"size = ");
	ft_putnbr(node->size);
	ft_putendl("");

	ft_putstr(PURPLE"ptr = ");
	print_hexa((unsigned long)node->ptr);
	ft_putendl("");
	
	ft_putstr(YELLOW"free = ");
	ft_putnbr(node->free);
	ft_putendl("");

	ft_putstr(GREY"flag = ");
	if (node->flag == 't')
		ft_putendl("TINY");
	else if (node->flag == 's')
		ft_putendl("SMALL");
	else
		ft_putendl("LARGE");

	ft_putstr(PINK"next = ");
	if (node->next)
		ft_putendl("NOT NULL");
	else
		ft_putendl("NULL");

	ft_putendl(""END);
	
}

void	DEBUG_calling_free_message()
{
	ft_putendl("free function called");
}

void	DEBUG_adress_to_free(void *addr)
{
	ft_putstr(GREEN"");
	ft_putstr("free addr             : ");
	print_hexa((unsigned long)addr);
	RC;
}

void	DEBUG_free_current_addr(void *ptr, size_t i)
{
	ft_putstr(YELLOW"(Node ");
	ft_putnbr(i);
	ft_putstr(") ");
	ft_putstr("Current addr : ");
	print_hexa((unsigned long)ptr);
	RC;
}

void	DEBUG_print_info_node(size_t i)
{
	t_block	*tmp;
	
	if (g_block == NULL)
		ft_putendl("NULL");
	tmp = g_block;
	ft_putendl(RED"============================================================="END);
	while (tmp && tmp->free == 1)
	{
		DEBUG_print_node(tmp, i);
		tmp = tmp->next;
		++i;
	}
}
