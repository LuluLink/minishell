#include "minishell.h"

int     verif_arg_export(t_elem_cmd *actual)
{
    int i;

    i = 0;
    t_elem_cmd *tmp;
    tmp = actual->next;
    while (tmp->cmd[i] != '\0' && tmp->cmd[i] != '=')
    {
        if ((tmp->cmd[i] >= '0' && tmp->cmd[i] <= '9') && i == 0)
            return (-1);
        if (tmp->cmd[i] < '0' || tmp->cmd[i] > 'z')
            return (-1);
        if (tmp->cmd[i] > '9' && tmp->cmd[i] < 'A')
            return (-1);
        if ((tmp->cmd[i] > 'Z' && tmp->cmd[i] < '_') || tmp->cmd[i] == '`')
            return (-1);
        if (tmp->cmd[i] == '\"')
        {
            i++;
            if (tmp->cmd[i] == '\0' || tmp->cmd[i] == '=')
                return (0);
        }
        i++;
    }
    return (0);
}

void    ft_export(t_elem_cmd *actual)
{
    int i;
    int verif_quote;
    char    *str;

    i = 0;
    verif_quote = 0;
    if (actual->next == NULL || actual->next->token != ARG)
    {
        t_elem_env *tmp;
        tmp = g_all.first_env;
        while (tmp != NULL)
        {
            ft_putstr("declare -x ");
            while (tmp->env[i] != '\0')
            {
                ft_putchar(tmp->env[i]);
                 if (tmp->env[i] == '=' && verif_quote == 0)
                {
                    ft_putchar('\"');
                    verif_quote = 1;
                }
                if (tmp->env[i + 1] == '\0' && verif_quote == 1)
                   ft_putchar('\"'); 
                i++;
            }
            i = 0;
            verif_quote = 0;
            tmp = tmp->next;
            ft_putchar('\n');
        }
        return ;
    }
    while (actual->next != NULL && actual->next->token == ARG)
    {
        if ((verif_arg_export(actual) == -1))
            printf("export : %s : indentifiant invalide\n", actual->next->cmd);
        str = ft_strdup(actual->next->cmd);
        insertion_end_env(str);
        actual = actual->next;
    }
}