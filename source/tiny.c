/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 07:36:01 by rabougue          #+#    #+#             */
/*   Updated: 2017/05/18 07:41:20 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/malloc.h"

t_block	g_tiny_block;

void	*alloc_tiny(size_t size)
{
	void	*allocation_famillial;

	ft_memset(&g_tiny_block, 0, sizeof(t_block));
	return (allocation_famillial);
}
