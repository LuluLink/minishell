/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2021/04/14 15:58:19 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_reset_fd(void)
{
	if (g_all.fdin != -1)
		close(g_all.fdin);
	if (g_all.fdout != -1)
		close(g_all.fdout);
	if (g_all.pipefdin != -1)
		close(g_all.pipefdin);
	if (g_all.pipefdout != -1)
		close(g_all.pipefdout);
	g_all.fdin = -1;
	g_all.fdout = -1;
	g_all.pipefdin = -1;
	g_all.pipefdout = -1;
	dup2(g_all.standardin, 0);
	dup2(g_all.standardout, 1);
}

void	replace_env(int j)
{
	static int	i;
	int			k;
	t_elem_cmd	*tmp;
	char		*str;

	i = (j == 0) ? 0 : i;
	k = i++;
	tmp = g_all.first_cmd;
	while (k > 0 && tmp && tmp->next)
	{
		while (tmp && tmp->token != SEMICOLON)
			tmp = tmp->next;
		if (tmp->token == SEMICOLON && tmp->next)
			tmp = tmp->next;
		k--;
	}
	while (tmp && tmp->token != SEMICOLON)
	{
		str = ft_strdup(tmp->cmd);
		tmp->cmd = check_dollar(tmp->cmd);
		if (ft_strcmp(str, tmp->cmd) != 0)
			check_multiple_words(tmp);
		free(str);
		tmp = tmp->next;
	}
}

void	execution_first(t_elem_cmd *actual, int pid)
{
	replace_env(0);
	ft_execution(actual);
	ft_reset_fd();
	waitpid(-1, &pid, 0);
	if (WIFEXITED(pid))
		pid = WEXITSTATUS(pid);
	if (g_all.dad == 1)
		g_all.exit_code = pid;
	if (g_all.child == 1)
	{
		free_list_cmd();
		free_list_env();
		free(g_all.buff);
		exit(g_all.exit_code);
	}
	reset_var();
}

void	ft_start_execution(t_elem_cmd *actual, int pid)
{
	execution_first(actual, pid);
	while (actual && actual->next)
	{
		actual = actual->next;
		if (actual && actual->next && actual->token == SEMICOLON)
		{
			replace_env(1);
			actual = actual->next;
			ft_execution(actual);
			ft_reset_fd();
			waitpid(-1, &pid, 0);
			if (WIFEXITED(pid))
				pid = WEXITSTATUS(pid);
			if (g_all.dad == 1)
				g_all.exit_code = pid;
			if (g_all.child == 1)
			{
				free_list_cmd();
				free_list_env();
				free(g_all.buff);
				exit(g_all.exit_code);
			}
			reset_var();
		}
	}
}

void	ft_execution(t_elem_cmd *actual)
{
	int ret;

	ret = 0;
	g_all.in_loop = 1;
	if (!actual || g_all.exit == 1 || !ft_check_sep())
		return ;
	if (actual->prev && actual->prev->token == DOUBLERIGHT)
		ft_doubleright(actual);
	if (actual->prev && actual->prev->token == RIGHT)
		ft_right(actual);
	if (actual->prev && actual->prev->token == LEFT)
		ft_left(actual);
	if (actual->prev && actual->prev->token == PIPE)
		ret = ft_pipe();
	if (actual->next != NULL && actual->next->token != SEMICOLON && ret != 1)
		ft_execution(actual->next);
	if (g_all.block_cmd == 0 && actual->token == CMD && ret != 1)
	{
		launch_cmd(actual);
		g_all.block_cmd = 1;
	}
}
