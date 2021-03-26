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