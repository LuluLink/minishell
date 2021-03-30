#include "minishell.h"

void    initialisation_struct()
{
    g_all.first_cmd = NULL;
    g_all.first_env = NULL;
	g_all.exit = 0;
	g_all.fdout = 0;
	g_all.fdin = 0;
	g_all.standardin = dup(0);
	g_all.standardout = dup(1);
    ft_aff_minishell();
}