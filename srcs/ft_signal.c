/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 15:41:26 by macbookpro        #+#    #+#             */
/*   Updated: 2021/04/07 15:41:27 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_signal_hander_c(int signal)
{
	if (signal == SIGINT)
	{
		if (g_all.child == 0)
		{
			write(STDERR_FILENO, "\n", 1);
			if (g_all.in_loop == 0)
				write(2, NEWLINE, ft_strlen(NEWLINE));
			g_all.ctrl_c = 1;
		}
	}
}

void	ft_signal_hander_backslash(int signal)
{
	if (signal == SIGQUIT)
	{
		write(STDERR_FILENO, "\b\b  ", 4);
	}
}
