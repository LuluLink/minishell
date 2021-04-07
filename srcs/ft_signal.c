#include "minishell.h"

void	ft_signal_hander_c(int signal)
{
	if (signal == SIGINT)
	{
		if (g_all.child == 0)
		{
			write(STDERR_FILENO, "\n", 1);
			write(1, NEWLINE, ft_strlen(NEWLINE));
			g_all.ctrl_c = 1;
		}
	}
}

void	ft_signal_hander_backslash(int signal)
{
	if (signal == SIGQUIT)
	{
		write(STDERR_FILENO, "\b\b  ", 4);
	}
}