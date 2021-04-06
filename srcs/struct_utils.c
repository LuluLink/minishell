#include "minishell.h"

void    initialisation_struct()
{
    g_all.first_cmd = NULL;
    g_all.first_env = NULL;
    g_all.cmd_lst = NULL;
    g_all.str = NULL;
	g_all.exit = 0;
    ft_aff_minishell();
}