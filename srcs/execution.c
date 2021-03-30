/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2021/03/29 19:05:17 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_reset_fd(void)
{
	if (g_all.fdin != -1)
		close(g_all.fdin);
	if (g_all.fdout != -1)
		close(g_all.fdout);
	g_all.fdin = -1;
	g_all.fdout = -1;
	dup2(g_all.standardin, 0);
	dup2(g_all.standardout, 1);
}

void	ft_start_execution(t_elem_cmd *actual)
{
	ft_execution(actual);
	ft_reset_fd();
	while (actual && actual->next)
	{
		actual = actual->next;
		if (actual && actual->next && actual->token == SEMICOLON)
		{
			actual = actual->next;
			ft_execution(actual);
			ft_reset_fd();

		}
	}
}

void	ft_execution(t_elem_cmd *actual)
{
	if (!actual || g_all.exit == 1)
		return ;
	if (actual->prev && actual->prev->token == DOUBLERIGHT)
		ft_doubleright(actual);
	if (actual->prev && actual->prev->token == RIGHT)
		ft_right(actual);
	if (actual->prev && actual->prev->token == LEFT)
		ft_left(actual);
	if (actual->prev && actual->prev->token == PIPE)
		printf("pipe\n");// ft_pipe(actual);
	if (actual->next != NULL && actual->next->token != SEMICOLON)
		ft_execution(actual->next);
	if (actual->token == CMD)
		launch_cmd(actual);
}
