#include "../include/malloc.h"

extern t_block	*meta_tiny;
extern t_block	*meta_small;
extern t_block	*meta_large;
extern void	*g_tiny_data;
extern void	*g_small_data;
extern void	*g_large_data;

void	DEBUG_print_allocated_zones()
{
	static size_t	i = 1;
	/*t_block	*tmp = meta_tiny;*/
	/*t_block	*tmp_2 = meta_small;*/
	/*t_block	*tmp_3 = meta_large;*/

	ft_putstr("Malloc call = ");
	ft_putnbr(i);
	RC;
	/*while (tmp->next && tmp->free == 1)*/
	/*{*/
		/*ft_putendl(GREEN"Tiny zone :");*/
		/*ft_putstr("size = ");*/
		/*ft_putnbr(tmp->size);*/
		/*ft_putstr(" addr tmp = ");*/
		/*print_hexa((unsigned int)tmp);*/
		/*ft_putstr(" addr tmp->ptr = ");*/
		/*print_hexa((unsigned int)tmp->ptr);*/
		/*tmp = tmp->next;*/
		/*RC ;*/
	/*}*/
	/*if (meta_small)*/
	/*{*/
		/*while (tmp_2->next && tmp_2->free == 1)*/
		/*{*/
			/*ft_putendl(PINK"Small zone :");*/
			/*ft_putstr("size = ");*/
			/*ft_putnbr(tmp_2->size);*/
			/*ft_putstr(" addr tmp_2 = ");*/
			/*print_hexa((unsigned int)tmp_2);*/
			/*ft_putstr(" addr tmp_2->ptr = ");*/
			/*print_hexa((unsigned int)tmp_2->ptr);*/
			/*tmp_2 = tmp_2->next;*/
			/*RC ;*/
		/*}*/
	/*}*/
	/*if (meta_large)*/
	/*{*/
		/*while (tmp_3->next && tmp_3->free == 1)*/
		/*{*/
			/*ft_putendl(CYAN"Large zone :");*/
			/*//=================================================================*/
			/*ft_putstr("size = ");*/
			/*ft_putnbr(tmp_3->size);*/
			/*RC ;*/
			/*//=================================================================*/
			/*ft_putstr("addr tmp_3 = ");*/
			/*print_hexa((unsigned int)tmp_3);*/
			/*RC ;*/
			/*//=================================================================*/
			/*ft_putstr("addr tmp_3->ptr = ");*/
			/*print_hexa((unsigned int)tmp_3->ptr);*/
			/*RC ;*/
			/*//=================================================================*/
			/*tmp_3 = tmp_3->next;*/
			/*ft_putstr("tmp_3 = ");*/
			/*print_hexa((unsigned int)tmp_3);*/
			/*RC ;*/
			/*RC ;*/
		/*}*/
	/*}*/
	/*ft_putendl(""END);*/
	++i;
}
