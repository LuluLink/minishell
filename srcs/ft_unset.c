#include "minishell.h"

void    ft_unset(char *str)
{
    int ret;
    t_elem_env *tmp;


    ret = ft_strlen(str);
    tmp = g_all.first_env;
    while (tmp != NULL)
    {
        //printf("env :%s    str :%s    ret :%d     strncmp %d\n", tmp->env, str, ret, ft_strncmp(tmp->env, str, ret));
        if ((ft_strncmp(tmp->env, str, ret) == 0))
        {
            suppression_middle_env(tmp);
            return ;
        }
        tmp = tmp->next;
    }
}