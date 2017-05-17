/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 05:59:09 by rabougue          #+#    #+#             */
/*   Updated: 2017/05/17 07:37:30 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/malloc.h"

void	*malloc(size_t size)
{
	void	*allocation_famillial;

	allocation_famillial = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (allocation_famillial == (void *) -1)
		ft_dprintf(2, "%s\n", strerror(errno));

	return (allocation_famillial);
}
