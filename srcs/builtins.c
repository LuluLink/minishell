#include "minishell.h"

// builtins : echo (-n), cd, pwd, export, unset, env, exit

int     check_path_cmd(char *path)
{
    int fd;
    
    fd = open(path, O_RDONLY);
    close(fd);
    if (fd == -1)
        return (0);
    return (1);
}

void    check_cmd(t_elem_cmd *tmp)
{
    char *path;
    char **files;
    
    if (!(path = chrenv(ft_strdup("PATH"))))
        path = ft_strdup("/bin:/usr/local/bin:/usr/bin:/bin:/usr/local/sbin");
    files = ft_split(path, ':');
    int i = 0;
    while (files[i])
    {
        files[i] = ft_strjoin(files[i], ft_strjoin(ft_strdup("/"), ft_strdup(tmp->cmd)));
        int j = check_path_cmd(files[i]);
        printf("path %2d, success : %2d : %s\n", i, j,files[i]);
        i++;
    }
    (void)tmp;
}

int     builtins_cmd(t_elem_cmd *tmp)
{
    if (ft_strcmp(tmp->cmd, "echo") == 0)
        printf("builtin echo\n");// ICI APPELER ECHO
    else if (ft_strcmp(tmp->cmd, "cd") == 0)
        printf("builtin cd\n");// ICI APPELER CD
    else if (ft_strcmp(tmp->cmd, "pwd") == 0)
        printf("builtin pwd\n");// ICI APPELER PWD
    else if (ft_strcmp(tmp->cmd, "export") == 0)
        printf("builtin export\n");// ICI APPELER EXPORT
    else if (ft_strcmp(tmp->cmd, "unset") == 0)
        printf("builtin unset\n");// ICI APPELER UNSET
    else if (ft_strcmp(tmp->cmd, "env") == 0)
        ft_env();
    else if (ft_strcmp(tmp->cmd, "exit") == 0)
        ft_exit();
    else
        return (0);
    return (1);
}

void    launch_cmd(t_elem_cmd *tmp)
{
    if (!builtins_cmd(tmp))
        check_cmd(tmp);
}