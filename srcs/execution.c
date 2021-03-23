#include "minishell.h"

void    ft_execution(t_elem_cmd *actual)
{
    if(actual->prev->token == DOUBLERIGHT)
       // ft_doubleright(actual);
    if(actual->prev->token == RIGHT)
        //ft_right(actual);
    if(actual->prev->token == LEFT)
       // ft_left(actual);
    if(actual->prev->token == PIPE)
       // ft_pipe(actual);
    if(actual->next != NULL && actual->next->token != SEMICOLON)
        ft_execution(actual->next);
    if(actual->token == CMD)
        launchcmd(actual);
}