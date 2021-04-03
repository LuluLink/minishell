/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2021/03/29 12:32:59 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_path_cmd(char *path)
{
	int fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

char	*check_cmd(t_elem_cmd *tmp)
{
	char	*path;
	char	**files;
	char	*cmd;
	int		i;

	if (!(path = chrenv(ft_strdup("PATH"))))
		path = ft_strdup("");
	files = ft_split(path, ':');
	i = 0;
	while (files[i])
	{
		files[i] = ft_strjoin(files[i],
		ft_strjoin(ft_strdup("/"), ft_strdup(tmp->cmd)));
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

int		builtins_cmd(t_elem_cmd *tmp)
{
	if (ft_strcmp(tmp->cmd, "echo") == 0)
		g_all.exit_code = ft_echo(tmp);
	else if (ft_strcmp(tmp->cmd, "cd") == 0)
		g_all.exit_code = ft_cd((tmp->next &&
		tmp->next->token != SEMICOLON) ? tmp->next->cmd : NULL);
	else if (ft_strcmp(tmp->cmd, "pwd") == 0)
		g_all.exit_code = ft_pwd();
	else if (ft_strcmp(tmp->cmd, "export") == 0)
		g_all.exit_code = ft_export(tmp);
	else if (ft_strcmp(tmp->cmd, "unset") == 0)
		g_all.exit_code = ft_unset(tmp);
	else if (ft_strcmp(tmp->cmd, "env") == 0)
		g_all.exit_code = ft_env(tmp);
	else if (ft_strcmp(tmp->cmd, "exit") == 0)
		ft_exit(tmp);
	else
		return (0);
	return (1);
}

void	ft_execve(char *path, char **cmd, char **env)
{
	pid_t	pid;
	int		status;
	char	*error;

	status = 0;
	pid = fork();
	if (pid == -1)
	{
		error = strerror(errno);
		ft_putstr_fd(error, 2);
		ft_putstr_fd("\n", 2);
		exit(0);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else if (WIFEXITED(pid))
		g_all.exit_code = WEXITSTATUS(pid);
	else if (execve(path, cmd, env) == -1)
	{
		error = strerror(errno);
		ft_putstr_fd(error, 2);
		ft_putstr_fd("\n", 2);
		exit(0);
	}
}

void	ft_create_path(char *path, t_elem_cmd *lst)
{
	t_elem_cmd	*tmp;
	char		**tab;
	char		**env;
	int			i;
	int			j;

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
	env = liste_env_to_wordtab();
	ft_execve(path, tab, env);
	free(path);
	free_double_char(env);
	free_double_char(tab);
}

void	launch_cmd(t_elem_cmd *tmp)
{
	char	*path;

	if (!builtins_cmd(tmp))
	{
		path = check_cmd(tmp);
		if (path)
			ft_create_path(path, tmp);
		else
			ft_create_path(ft_strdup(tmp->cmd), tmp);
	}
}
