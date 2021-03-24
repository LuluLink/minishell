#include "minishell.h"

void    suppression_begining_env(t_elem_env *liste)
{
    t_elem_env *tmp;
    tmp = liste;
    g_all.first_env = tmp->next;
    g_all.first_env->prev = NULL;
    free(tmp->env);
    free(tmp);
}

void   suppression_end_env(t_elem_env *liste)
{
    t_elem_env *tmp;
    tmp = liste;
    tmp->prev->next = NULL;
    free(tmp->env);
    free(tmp);
}

void suppression_last_env()
{
    t_elem_env *tmp;
    tmp = g_all.first_env;
    g_all.first_env = NULL;
    free(tmp->env);
    free(tmp);
}

void    suppression_middle_env(t_elem_env *liste)
{
    t_elem_env *tmp;
    tmp = liste;
    if (tmp->prev == NULL)
    {
        suppression_begining_env(liste);
        return ;
    }
    if (tmp->next == NULL)
    {
        suppression_end_env(liste);
        return ;
    }
    if (tmp->prev == NULL && tmp->next == NULL)
    {
        suppression_last_env();
        return ;
    }
    tmp->prev->next = tmp->next;
    tmp->next->prev = tmp->prev;
    free(tmp->env);
    free(tmp);
}

char    **liste_env_to_wordtab()
{
    char    **dest;
    int     i;
    t_elem_env *tmp;

    i = 0;
    tmp = g_all.first_env;
    while (tmp != NULL)
    {
        tmp = tmp->next;
        i++;
    }
    dest = malloc(sizeof(char*) * (i + 1));
    dest[i] = NULL;
    tmp = g_all.first_env;
    i = 0;
    while (tmp != NULL)
    {
        dest[i] = ft_strdup(tmp->env);
        i++;
        tmp = tmp->next;
    }
    return (dest);
}