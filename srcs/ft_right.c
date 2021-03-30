#include "minishell.h"

void	ft_right(t_elem_cmd *actual)
{
	g_all.fdout = open(actual->cmd, O_CREAT | O_TRUNC | O_WRONLY , S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (g_all.fdout == -1)
	{
		ft_putstr_fd("Cant open file : ", 2);
		ft_putstr_fd(actual->cmd, 2);
		ft_putstr_fd("\n", 2);
		g_all.exit = 1;
	}
	dup2(g_all.fdout, STDOUT_FILENO);
}

void	ft_doubleright(t_elem_cmd *actual)
{
	g_all.fdout = open(actual->cmd, O_CREAT | O_APPEND | O_WRONLY , S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (g_all.fdout == -1)
	{
		ft_putstr_fd("Cant open file : ", 2);
		ft_putstr_fd(actual->cmd, 2);
		ft_putstr_fd("\n", 2);
		g_all.exit = 1;
	}
	dup2(g_all.fdout, STDOUT_FILENO);
}

void	ft_left(t_elem_cmd *actual)
{
	g_all.fdin = open(actual->cmd, O_RDONLY , S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (g_all.fdin == -1)
	{
		ft_putstr_fd("Cant open file : ", 2);
		ft_putstr_fd(actual->cmd, 2);
		ft_putstr_fd("\n", 2);
		g_all.exit = 1;
	}
	dup2(g_all.fdin, STDIN_FILENO);
}