#include "minishell.h"

/*
but de la fonction : trouver le bon token
action de la fonction : trouve le bon token pour str
str : le mot qui va obtenir un token
tmp : element tampon de la liste chaine cmd
*/

void    search_token(char *str, t_elem_cmd *tmp)
{
    if (str[0] == '|')
    {
        tmp->token = PIPE;
        return ;
    }
    if (str[0] == '>' && str[1] == '>')
    {
        tmp->token = DOUBLERIGHT;
        return ;
    }
    if (str[0] == '>' && str[1] == '\0')
    {
        tmp->token = RIGHT;
        return ;
    }
    if (str[0] == '<' && str[1] == '\0')
    {
        tmp->token = LEFT;
        return ;
    }
    if (str[0] == ';')
    {
        tmp->token = SEMICOLON;
        return ;
    }
    if (tmp->prev == NULL || tmp->prev->token == SEMICOLON || tmp->prev->token == PIPE)
    {
        tmp->token = CMD;
        return ;
    }
    tmp->token = ARG;
    return ;
}

/*
but de la fct: attribuer un token a chaque mot
action : parcourt la liste chainés et appelle search token
*/

void    give_list_token()
{
    t_elem_cmd *tmp;

    tmp = g_all.first_cmd;
    while (tmp != NULL)
    {
        search_token(tmp->cmd, tmp);
        tmp = tmp->next;
    }
}