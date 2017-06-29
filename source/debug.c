#include "../include/malloc.h"

extern t_memory	g_memory;

static size_t	print_data_mem(t_block *zone)
{
	size_t	total;

	total = 0;
	while (zone)
	{
		if (zone->free == 1)
		{
			print_hexa((unsigned int)zone->ptr);
			ft_putstr(" - ");
			print_hexa((unsigned int)zone->ptr + zone->size);
			ft_putstr(" : ");
			ft_putnbr(zone->size);
			ft_putendl(" octets");
			total += zone->size;
		}
		zone = zone->next;
	}
	RC;
	return (total);
}

void	show_alloc_mem()
{
	size_t	total;

	total = 0;
	if (g_memory.meta_tiny && g_memory.meta_tiny->free == 1)
	{
		ft_putstr(YELLOW"\e[1mTINY : ");
		print_hexa((unsigned int)g_memory.meta_tiny);
		RC;
		total += print_data_mem(g_memory.meta_tiny);
	}
	if (g_memory.meta_small && g_memory.meta_small->free == 1)
	{
		ft_putstr(ORANGE"SMALL : ");
		print_hexa((unsigned int)g_memory.meta_small);
		RC;
		total += print_data_mem(g_memory.meta_small);
	}
	if (g_memory.meta_large && g_memory.meta_large->free == 1)
	{
		ft_putstr(RED"LARGE : ");
		print_hexa((unsigned int)g_memory.meta_large);
		RC;
		total += print_data_mem(g_memory.meta_large);
	}
	ft_putstr(PURPLE"Total : ");
	ft_putnbr(total);
	ft_putendl(" octets"END);
}

void	DEBUG_print_allocated_zones()
{
	static size_t	i = 1;
	t_block	*tmp = g_memory.meta_tiny;
	t_block	*tmp_2 = g_memory.meta_small;
	t_block	*tmp_3 = g_memory.meta_large;

	ft_putstr("Malloc call = ");
	ft_putnbr(i);
	RC;

	while (tmp->next && tmp->free == 1)
	{
		ft_putendl(GREEN"Tiny zone :");
		ft_putstr("size = ");
		ft_putnbr(tmp->size);
		ft_putstr(" addr tmp = ");
		print_hexa((unsigned int)tmp);
		ft_putstr(" addr tmp->ptr = ");
		print_hexa((unsigned int)tmp->ptr);
		tmp = tmp->next;
		RC ;
	}
	if (g_memory.meta_small)
	{
		while (tmp_2->next && tmp_2->free == 1)
		{
			ft_putendl(PINK"Small zone :");
			ft_putstr("size = ");
			ft_putnbr(tmp_2->size);
			ft_putstr(" addr tmp_2 = ");
			print_hexa((unsigned int)tmp_2);
			ft_putstr(" addr tmp_2->ptr = ");
			print_hexa((unsigned int)tmp_2->ptr);
			tmp_2 = tmp_2->next;
			RC ;
		}
	}
	if (g_memory.meta_large)
	{
		while (tmp_3->next && tmp_3->free == 1)
		{
			ft_putendl(CYAN"Large zone :");
			//=================================================================
			ft_putstr("size = ");
			ft_putnbr(tmp_3->size);
			RC ;
			//=================================================================
			ft_putstr("addr tmp_3 = ");
			print_hexa((unsigned int)tmp_3);
			RC ;
			//=================================================================
			ft_putstr("addr tmp_3->ptr = ");
			print_hexa((unsigned int)tmp_3->ptr);
			RC ;
			//=================================================================
			tmp_3 = tmp_3->next;
			ft_putstr("tmp_3 = ");
			print_hexa((unsigned int)tmp_3);
			RC ;
			RC ;
		}
	}
	ft_putendl(""END);
	++i;
}
