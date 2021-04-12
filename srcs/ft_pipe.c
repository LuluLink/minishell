/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 15:41:22 by macbookpro        #+#    #+#             */
/*   Updated: 2021/04/07 15:41:23 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	error_pipe(void)
{
	char	*error;

	error = strerror(errno);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	exit(0);
}

int		ft_pipe(void)
{
	int		fd[2];
	pid_t	pid;

	if ((pipe(fd) == -1))
		error_pipe();
	if ((pid = fork()) == -1)
		error_pipe();
	if (pid == 0)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		g_all.child = 1;
		g_all.pipefdin = fd[0];
		return (2);
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], 1);
		g_all.pipefdout = fd[1];
		g_all.dad = 1;
		return (1);
	}
}
