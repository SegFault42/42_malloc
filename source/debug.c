#include "../include/malloc.h"

extern t_block	*meta_tiny;
extern t_block	*meta_small;
extern void	*g_tiny_data;
extern void	*g_small_data;

void	DEBUG_print_allocated_zones()
{
	static size_t	i = 1;
	t_block	*tmp = meta_tiny;
	t_block	*tmp_2 = meta_small;

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
	if (meta_small)
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
	ft_putendl(""END);
	++i;
}
