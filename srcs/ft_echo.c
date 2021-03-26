#include "minishell.h"

void    print_echo_arg(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '\"')
        {
            i++;
            while (str[i] != '\"' && str[i] != '\0')
                ft_putchar(str[i++]);
            i++;
        }
        if (str[i] == '\'')
        {
            i++;
             while (str[i] != '\'' && str[i] != '\0')
                ft_putchar(str[i++]);
            i++;
        }
        if (str[i] != '\0')
            ft_putchar(str[i++]);
    }
}

t_elem_cmd     *verif_n_echo(t_elem_cmd *actual)
{
    int i;

    while (actual != NULL && actual->token == ARG)
    {
        if ((ft_strncmp(actual->cmd, "-n", 2) != 0))
            return (actual);
        if ((ft_strncmp(actual->cmd, "-n", 2) == 0))
        {
            i = 2;
            while (actual->cmd[i] != '\0')
            {
                if (actual->cmd[i] != 'n')
                    return (actual);
                i++;
            }
        }
        actual = actual->next;
    }
    return (actual);
}

void    ft_echo(t_elem_cmd *actual)
{
    t_elem_cmd *tmp;
    int verif;
    
    if (actual->next == NULL)
    {
        putchar('\n');
        return ;
    }
    actual = actual->next;
    tmp = verif_n_echo(actual);
    if (tmp != actual)
        verif = 1;
    actual = tmp;
    while (actual != NULL && actual->token == ARG)
    {
        print_echo_arg(actual->cmd);
        if (actual->next != NULL && actual->token == ARG)
            ft_putchar(' ');
        actual = actual->next;
    }
    if ((verif == 0))
        ft_putchar('\n');
}