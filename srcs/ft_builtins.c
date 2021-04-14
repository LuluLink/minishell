/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2021/04/07 15:40:55 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	ft_send_error(void)
{
	char	*error;

	error = strerror(errno);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	if (errno == EAGAIN)
		exit(126);
	else
		exit(127);
}

void	ft_execve(char *path, char **cmd, char **env)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
		ft_send_error();
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else if (execve(path, cmd, env) == -1)
		ft_send_error();
	else if (WIFEXITED(pid))
		g_all.exit_code = WEXITSTATUS(pid);
}

void	ft_create_path(char *path, t_elem_cmd *lst, t_elem_cmd *tmp)
{
	char		**mytab;
	char		**env;
	int			i;
	int			j;

	i = 0;
	while (tmp->next && tmp->next->token == ARG)
	{
		tmp = tmp->next;
		i++;
	}
	mytab = malloc(sizeof(char*) * (++i + 1));
	j = 0;
	while (i-- > 0)
	{
		mytab[j++] = ft_strdup(lst->cmd);
		lst = lst->next;
	}
	mytab[j] = NULL;
	env = liste_env_to_wordtab();
	ft_execve(path, mytab, env);
	free(path);
	free_double_char(env);
	free_double_char(mytab);
}

void	launch_cmd(t_elem_cmd *tmp)
{
	char	*path;

	if (!builtins_cmd(tmp))
	{
		path = check_cmd(tmp);
		if (path)
			ft_create_path(path, tmp, tmp);
		else
			ft_create_path(ft_strdup(tmp->cmd), tmp, tmp);
	}
}
