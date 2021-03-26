#include "minishell.h"

void	ft_pwd(void)
{
	char *tmp;

	tmp = getcwd(NULL, 0);
	if (!tmp && errno == 2)
		ft_putstr_fd("pwd : error\n", 2);
	else
	{
		ft_putstr_fd(tmp, 1);
		ft_putstr_fd("\n", 1);
		free(tmp);
	}
}