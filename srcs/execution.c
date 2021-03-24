#include "minishell.h"

void    ft_execution(t_elem_cmd *actual)
{
    if(actual->prev && actual->prev->token == DOUBLERIGHT)
       printf("double right\n");// ft_doubleright(actual);
    if(actual->prev && actual->prev->token == RIGHT)
        printf("right\n");//ft_right(actual);
    if(actual->prev && actual->prev->token == LEFT)
       printf("left\n");// ft_left(actual);
    if(actual->prev && actual->prev->token == PIPE)
       printf("pipe\n");// ft_pipe(actual);
    if(actual->next != NULL && actual->next->token != SEMICOLON)
        ft_execution(actual->next);
    if(actual->token == CMD)
        launch_cmd(actual);
}