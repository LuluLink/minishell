#include "minishell.h"

void    ft_execution(t_elem_cmd *actual)
{
    if (actual->prev != NULL)
    {
        if(actual->prev->token == DOUBLERIGHT)
           return ;// ft_doubleright(actual);
        if(actual->prev->token == RIGHT)
            return ;//ft_right(actual);
        if(actual->prev->token == LEFT)
           return ;// ft_left(actual);
        if(actual->prev->token == PIPE)
           return ;// ft_pipe(actual);
    }
    if(actual->next != NULL && actual->next->token != SEMICOLON)
        ft_execution(actual->next);
    if(actual->token == CMD)
        launch_cmd(actual);
}