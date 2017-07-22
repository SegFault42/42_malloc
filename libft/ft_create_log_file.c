/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_log_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/22 20:10:35 by rabougue          #+#    #+#             */
/*   Updated: 2017/07/22 20:10:38 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

void	ft_create_log_file(char *name, char *str)
{
	int	fd;

	fd = open(name, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	if (fd != -1)
	{
		write(fd, str, ft_strlen(str));
		close(fd);
	}
}
