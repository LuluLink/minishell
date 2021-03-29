#include "minishell.h"

void	ft_right(t_elem_cmd *actual)
{
	int fd;

	fd = open(actual->cmd, O_CREAT | O_TRUNC | O_WRONLY , S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	printf("fd :%d\n", fd);
	if (fd == -1)
	{
		ft_putstr_fd("Cant open file : ", 2);
		ft_putstr_fd(actual->cmd, 2);
		ft_putchar_fd('\n', 2);
		g_all.exit = 1;
	}
}