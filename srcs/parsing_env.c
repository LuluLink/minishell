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
            verif = 1;
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
            verif = 1;
        i++;
    }
    return (tmp);
}

char *first_is_nbr(char *str)
{
    int i;
    int j;
    char *dest;

    j = 1;
    i = ft_strlen(str) - 1;
    dest = malloc(sizeof(char) *i + 1);
    dest[i] = '\0';
    i = 0;
    while (dest[i] != '\0')
    {
        dest[i] = str[j];
        i++;
        j++;
    }
    return (dest);
}

char    *chrenv(char *str)
{
    int i;
    int size;
    char *dest;
    t_elem_env *tmp;

    i = 0;
    tmp = g_all.first_env;
    dest = NULL;
    while (tmp != NULL)
    {
        size = ft_strlen(str);
        if ((ft_strncmp(tmp->env, str, size) == 0))
        {
            i = len_value(tmp->env);
            dest = fill_with_env_value(i, tmp->env);
            return (dest);
        }
        tmp = tmp->next;
    }
    if (str[0] >= '0' && str[0] <= '9')
    {
        dest = first_is_nbr(str);
    }
    return (dest);
}