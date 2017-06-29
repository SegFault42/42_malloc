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
