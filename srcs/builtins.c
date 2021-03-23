#include "minishell.h"

// builtins : echo (-n), cd, pwd, export, unset, env, exit

int     builtins_cmd(t_elem_cmd *tmp)
{
    if (ft_strcmp(tmp->cmd, "echo") == 0)
        return (1);// ICI APPELER ECHO
    else if (ft_strcmp(tmp->cmd, "cd") == 0)
        return (1);// ICI APPELER CD
    else if (ft_strcmp(tmp->cmd, "pwd") == 0)
        return (1);// ICI APPELER PWD
    else if (ft_strcmp(tmp->cmd, "export") == 0)
        return (1);// ICI APPELER EXPORT
    else if (ft_strcmp(tmp->cmd, "unset") == 0)
        return (1);// ICI APPELER UNSET
    else if (ft_strcmp(tmp->cmd, "env") == 0)
        return (1);// ICI APPELER ENV
    else if (ft_strcmp(tmp->cmd, "exit") == 0)
        return (1);// ICI APPELER EXIT
    else
        return (0);
    return (1);
}

void    launch_cmd(t_elem_cmd *tmp)
{
    builtins_cmd(tmp);
}