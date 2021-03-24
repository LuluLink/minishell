#include "minishell.h"

// builtins : echo (-n), cd, pwd, export, unset, env, exit

int     check_path_cmd(char *path)
{
    int fd;
    
    fd = open(path, O_RDONLY);
    if (fd == -1)
        return (0);
    close(fd);
    return (1);
}

char    *check_cmd(t_elem_cmd *tmp)
{
    char    *path;
    char    **files;
    char    *cmd;
    int     i;
    
    path = chrenv(ft_strdup("PATH"));
    files = ft_split(path, ':');
    i = 0;
    while (files && files[i])
    {
        files[i] = ft_strjoin(files[i], ft_strjoin(ft_strdup("/"), ft_strdup(tmp->cmd)));
        if (check_path_cmd(files[i]))
        {
            cmd = ft_strdup(files[i]);
            free_double_char(files);
            free(path);
            return (cmd);
        }
        i++;
    }
    free_double_char(files);
    free(path);
    return (NULL);
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
        ft_export(tmp);
    else if (ft_strcmp(tmp->cmd, "unset") == 0)
        ft_unset(tmp->next->cmd);
    else if (ft_strcmp(tmp->cmd, "env") == 0)
        ft_env();
    else if (ft_strcmp(tmp->cmd, "exit") == 0)
        ft_exit();
    else
        return (0);
    return (1);
}

void	ft_execve(char *path, char **cmd)
{
	pid_t	pid = 0;
	int		status = 0;
    char    *error;

	pid = fork();
	if (pid == -1)
    {
        error = strerror(errno);
        ft_putstr(error);
        ft_putchar('\n');
        exit(0);
    }
	else if (pid > 0)
    {
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
    else if (execve(path, cmd, NULL) == -1)
    {
        error = strerror(errno);
        ft_putstr(error);
        ft_putchar('\n');
        exit(0);
    }
}

void    ft_create_path(char *path, t_elem_cmd *lst)
{
    t_elem_cmd  *tmp;
    char        **tab;
    int         i;
    int         j;

    tmp = lst;
    i = 0;
    while (tmp->next && tmp->next->token == ARG)
    {
        tmp = tmp->next;
        i++;
    }
    tab = malloc(sizeof(char*) * (++i + 1));
    j = 0;
    while (i-- > 0)
    {
        tab[j++] = ft_strdup(lst->cmd);
        lst = lst->next;
    }
    tab[j] = NULL;
    if (path)
        ft_execve(path, tab);
    else
        ft_execve(tab[0], tab);
    free(path);
    free_double_char(tab);
}

void    launch_cmd(t_elem_cmd *tmp)
{
    char    *path;
    if (!builtins_cmd(tmp))
    {
        path = check_cmd(tmp);
        ft_create_path(path, tmp);
    }
}