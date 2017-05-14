/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/11 19:28:43 by rabougue          #+#    #+#             */
/*   Updated: 2017/04/06 20:41:53 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

void	ft_2d_tab_free(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_strdel(&tab[i]);
		++i;
	}
	free(tab);
	tab = NULL;
}
