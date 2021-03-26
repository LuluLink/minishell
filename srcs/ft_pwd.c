#include "minishell.h"

void    pwd_env(char *str)
{
    t_elem_env *tmp = g_all.first_env;
    while(tmp->next && ft_strncmp(tmp->env, "PWD=", 4) == 0)
        tmp = tmp->next;
    if (ft_strncmp(tmp->env, "PWD=", 4) == 0)
    {
        free(tmp->env);
        tmp->env = ft_strjoin(ft_strdup("PWD="), str);
    }
}

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
        pwd_env(tmp);
		free(tmp);
	}
}