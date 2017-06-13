#include "../include/malloc.h"

extern t_block	*g_block;

void	DEBUG_calling_malloc()
{
	if (DEBUG_CALLING_MALLOC == 0)
		return ;
	static size_t iter = 1;

	ft_putstr(WHITE"Calling malloc ");
	ft_putnbr(iter);
	ft_putstr(" time\n"END);
	++iter;
}

void	DEBUG_print_node(t_block *node, int i)
{
	if (DEBUG_PRINT_NODE == 0)
		return ;
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
	else if (node->flag == 'l')
		ft_putendl("LARGE");
	else
		ft_putendl(RED"Not set"END);

	ft_putstr(PINK"next = ");
	if (node->next)
		ft_putendl("NOT NULL");
	else
		ft_putendl("NULL");

	ft_putendl(""END);
}

void	DEBUG_calling_free_message()
{
	if (DEBUG_CALLING_FREE_MESSAGE == 0)
		return ;
	ft_putendl("free function called");
}

void	DEBUG_address_to_free(void *addr)
{
	if (DEBUG_ADDRESS_TO_FREE == 0)
		return ;
	ft_putstr(GREEN"");
	ft_putstr("free addr             : ");
	print_hexa((unsigned long)addr);
	RC;
}

void	DEBUG_free_current_addr(void *ptr, size_t i)
{
	if (DEBUG_FREE_CURRENT_ADDR == 0)
		return ;
	ft_putstr(YELLOW"(Node ");
	ft_putnbr(i);
	ft_putstr(") ");
	ft_putstr("Current addr : ");
	print_hexa((unsigned long)ptr);
	RC;
}

void	DEBUG_print_info_node(size_t i)
{
	if (DEBUG_PRINT_INFO_NODE == 0)
		return ;
	t_block	*tmp;
	
	if (g_block == NULL)
		ft_putendl("NULL");
	tmp = g_block;
	ft_putendl(RED"============================================================="END);
	while (tmp/* && tmp->free == 1*/)
	{
		DEBUG_print_node(tmp, i);
		tmp = tmp->next;
		++i;
	}
}

void	DEBUG_show_ret_mmap(int ret)
{
	if (DEBUG_SHOW_RET_MMAP == 0)
		return ;

	ft_putstr("MMAP return : ");
	if (ret == EACCES)
		ft_putstr("EACCES");
	else if (ret == EAGAIN)
		ft_putstr("EAGAIN");
	else if (ret == EBADF)
		ft_putstr("EBADF");
	else if (ret == EINVAL)
		ft_putstr("EINVAL");
	else if (ret == ENFILE)
		ft_putstr("ENFILE");
	else if (ret == ENODEV)
		ft_putstr("ENODEV");
	else if (ret == ENOMEM)
		ft_putstr("ENOMEM");
	else if (ret == EPERM)
		ft_putstr("EPERM");
	else if (ret == ETXTBSY)
		ft_putstr("ETXTBSY");
	else
		ft_putstr("SUCCESS");
	ft_putendl("");
}

void	DEBUG_print_ctrl_g_block(t_block *ctrl, t_block *g_block)
{
	if (DEBUG_PRINT_CTRL_G_BLOCK == 0)
		return ;
		
	ft_putstr("addr ctrl : ");
	print_hexa((unsigned int)ctrl);
	ft_putendl("");
	ft_putstr("addr g_block : ");
	print_hexa((unsigned int)g_block);
	ft_putendl("");
}
