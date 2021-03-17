#include "minishell.h"

int     len_value(char *str)
{
    int i;
    int j;
    int verif;

    i = 0;
    j = 0;
    verif = 0;
    while (str[i] != '\0')
    {
        if (verif == 1)// on incremente après avoir passer le premier =
            j++;
        if (str[i] == '=' && verif == 0)
            verif == 1;
        i++;
    }
    return (j);
}

char    *fill_with_env_value(int i, char *str)
{
    char *tmp;
    int j;
    int verif;

    j = 0;
    verif = 0;
    tmp = malloc(sizeof(char) * (i + 1));
    tmp[i] = '\0';
    i = 0;
    while (str[i] != '\0')
    {
        if (verif == 1)// on copie après le premier = passer
        {
            tmp[j] = str[i];
            j++;
        }
        if (str[i] == '=' && verif == 0)
            verif == 1;
        i++;
    }
    return (tmp);
}

char    *chrenv(char *str, t_struct_all *g_all)
{
    int i;
    char *tmp;
    t_elem_env *tmp;

    i = 0;
    tmp->next = g_all->first_env;
    while (tmp->next != NULL)
    {
        if (ft_strcmp(tmp->env, str) == 0)
        {
            i = len_value(tmp->env);
            tmp = fill_with_env_value(i, str);
            return (tmp);
        }
        tmp->next = tmp->next->next;
    }
    return (NULL);
}