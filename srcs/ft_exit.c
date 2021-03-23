#include "minishell.h"

void    ft_exit()
{
    free_list_cmd();
    free_list_env();
    free(g_all.buff);
    exit(0);
}