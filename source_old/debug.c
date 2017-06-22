#include "../include/malloc.h"

extern t_block	*g_tiny;
extern t_block	*g_small;
extern t_block	*g_large;

void	DEBUG_calling_malloc()
{
	if (DEBUG_CALLING_MALLOC == 0)
		return ;
	static size_t iter = 1;

	ft_putstr(WHITE"Calling malloc ");
	ft_putnbr(iter);
	ft_putstr(" time\n"END);
	/*if (iter == 1)*/
		/*sleep(1);*/
	++iter;
}

void	DEBUG_print_node(t_block *tiny, t_block *small, t_block *large, int i)
{
	if (DEBUG_PRINT_NODE == 0)
		return ;
	if (tiny)
	{
		ft_putstr(ORANGE"Tiny Node ");
		ft_putnbr(i);
		ft_putstr(" :");
		if (!small)
			RC;
	}
	if (small)
	{
		ft_putstr(ORANGE"			SMALL Node ");
		ft_putnbr(i);
		ft_putstr(" :");
	}
	if (large)
	{
		ft_putstr(ORANGE"		LARGE Node ");
		ft_putnbr(i);
		ft_putendl(" :");
	}

	if (tiny)
	{
		ft_putstr(CYAN"size = ");
		ft_putnbr(tiny->size);
		if (!small)
			RC;
	}
	if (small)
	{
		ft_putstr(CYAN"			size = ");
		ft_putnbr(small->size);
		ft_putstr("");
	}
	if (large)
	{
		ft_putstr(CYAN"			size = ");
		ft_putnbr(large->size);
		ft_putendl("");
	}

	if (tiny)
	{
		ft_putstr(PURPLE"tiny->ptr = ");
		print_hexa((unsigned long)tiny->ptr);
		if (!small)
			RC;
	}
	if (small)
	{
		ft_putstr(PURPLE"		small->ptr = ");
		print_hexa((unsigned long)small->ptr);
		ft_putstr("");
	}
	if (large)
	{
		ft_putstr(PURPLE"	large->ptr = ");
		print_hexa((unsigned long)large->ptr);
		ft_putendl("");
	}
	
	if (tiny)
	{
		ft_putstr(YELLOW"free = ");
		ft_putnbr(tiny->free);
		if (!small)
			RC;
	}
	if (small)
	{
		ft_putstr(YELLOW"			free = ");
		ft_putnbr(small->free);
		ft_putstr("");
	}
	if (large)
	{
		ft_putstr(YELLOW"			free = ");
		ft_putnbr(large->free);
		ft_putendl("");
	}
	
	if (tiny)
	{
		ft_putstr(GREY"flag = ");
		if (tiny->flag == 't')
			ft_putstr("TINY");
		else if (tiny->flag == 's')
			ft_putstr("SMALL");
		else if (tiny->flag == 'l')
			ft_putstr("LARGE");
		else
			ft_putstr(RED"Not set"END);
		if (!small)
			RC;
	}
	if (small)
	{
		ft_putstr(GREY"			flag = ");
		if (small->flag == 't')
			ft_putstr("TINY");
		else if (small->flag == 's')
			ft_putstr("SMALL");
		else if (small->flag == 'l')
			ft_putstr("LARGE");
		else
			ft_putstr(RED"Not set"END);
	}
	if (large)
	{
		ft_putstr(GREY"			flag = ");
		if (large->flag == 't')
			ft_putendl("TINY");
		else if (large->flag == 's')
			ft_putendl("SMALL");
		else if (large->flag == 'l')
			ft_putendl("LARGE");
		else
			ft_putendl(RED"Not set"END);
	}
	
	if (tiny)
	{
		ft_putstr(PINK"next = ");
		if (tiny->next)
			ft_putstr("NOT NULL");
		else
			ft_putstr("NULL");
		if (!small)
			RC;
	}
	if (small)
	{
		ft_putstr(PINK"			next = ");
		if (small->next)
			ft_putstr("NOT NULL");
		else
			ft_putstr("NULL");
	}
	if (large)
	{
		ft_putstr(PINK"			next = ");
		if (large->next)
			ft_putendl("NOT NULL");
		else
			ft_putendl("NULL");
	}
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
	t_block	*tmp_tiny = g_tiny;
	t_block	*tmp_small = g_small;
	t_block	*tmp_large = g_large;

	ft_putendl(RED"============================================================="END);
	while (tmp_tiny->next/* && tmp->free == 1*/)
	{
		DEBUG_print_node(tmp_tiny, tmp_small, tmp_large, i);
		if (tmp_tiny->next)
			tmp_tiny = tmp_tiny->next;
		if (g_small)
			if (tmp_small->next)
				tmp_small = tmp_small->next;
		if (g_large)
			if (tmp_large->next)
				tmp_large = tmp_large->next;
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

void	DEBUG_print_ctrl_g_tiny(t_block *ctrl, t_block *g_block)
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
