#include "minishell.h"

int	ft_pipe(void)
{
	int		fd[2];
	pid_t	pid;
	char	*error;

	if ((pipe(fd) == -1))
	{
		error = strerror(errno);
		ft_putstr_fd(error, 2);
		ft_putstr_fd("\n", 2);
		exit(0);
	}
	if ((pid = fork()) == -1)
	{
		error = strerror(errno);
		ft_putstr_fd(error, 2);
		ft_putstr_fd("\n", 2);
		exit(0);
	}
	if (pid == 0)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		g_all.child = 1;
		g_all.pipefdin = fd[0];
		return (2);
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], 1);
		g_all.pipefdout = fd[1];
		g_all.child = 0;
		return (1);
	}

}