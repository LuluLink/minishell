/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 16:02:08 by macbookpro        #+#    #+#             */
/*   Updated: 2021/04/15 15:29:11 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*keep_printable(char *str)
{
	char *a;

	if (g_all.arrow == 1 || g_all.arrow == 2)
	{
		a = ft_strndup(str, ft_strlen(str) - 2);
		free(str);
	}
	else
		a = str;
	return (a);
}

void	ft_supp(char *str, int j)
{
	int i;

	while (j-- > 0)
	{
		i = 0;
		while (str[i])
			i++;
		if (i > 0)
			i -= 1;
		str[i] = '\0';
	}
}

void	if_arrow(char **line)
{
	if (g_all.arrow == 3 || g_all.arrow == 4)
		ft_supp(*line, ((g_all.arrow == 4) ? 2 : 1));
	if (g_all.ctrl_d == 1 && !ft_strlen(*line))
		quit_minishell();
	else
		g_all.ctrl_d = 0;
	if (g_all.arrow == 0 && ft_strlen(*line) > 0)
	{
		cmd_rm_last();
		insertion_end_lst(*line);
	}
	if (g_all.arrow == 1 || g_all.arrow == 2)
	{
		if (g_all.index == lst_len() - 1)
		{
			cmd_rm_last();
			insertion_end_lst(*line);
		}
		free(*line);
		*line = NULL;
		cmd_histo();
	}
	else if (g_all.arrow == 0)
		g_all.index = lst_len();
}
