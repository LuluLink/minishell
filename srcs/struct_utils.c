#include "minishell.h"

void    initialisation_struct()
{
    g_all.first_cmd = NULL;
    g_all.first_env = NULL;
    ft_aff_minishell();
}