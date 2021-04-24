/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2021/04/21 20:39:39 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_cmd_c(char *buff)
{
	if (g_all.ctrl_c == 1)
	{
		g_all.a = buff[0];
		buff[0] = '\n';
	}
	check_arrow(&buff[0]);
}

char	*recurs(int index, int *ret, int fd)
{
	char	buff[1];
	char	*str;
	int		test;

	test = read(fd, buff, 1);
	check_cmd_c(&buff[0]);
	if (test == 0)
		buff[0] = 0;
	if (buff[0] == '\n' || buff[0] == 0 || g_all.ctrl_c != 0)
	{
		if (!(str = malloc(sizeof(char) * index + 1)))
			return (0);
		str[index] = 0;
		*ret = 1;
		if (buff[0] == 0)
			*ret = 0;
		return (str);
	}
	else
	{
		if (!(str = recurs(index + 1, ret, fd)))
			return (0);
		str[index] = buff[0];
	}
	return (str);
}

void	init_gnl(char **line)
{
	struct termios	term;

	g_all.arrow = 1;
	g_all.cursor = 0;
	g_all.cursor_x = 3;
	if (g_all.a)
	{
		check_arrow(&g_all.a);
		*line = free_last();
	}
	else
		*line = NULL;
	insertion_end_lst("");
	g_all.index = lst_len() - 1;
	tcgetattr(0, &term);
	term.c_lflag DISABLE_CANON ~(ICANON);
	tcsetattr(0, 0, &term);
}

void	end_gnl(char **line)
{
	if (g_all.ctrl_c == 1)
		cmd_rm_last();
	if (g_all.str)
		free(g_all.str);
	g_all.str = NULL;
	if (ft_strcmp(*line, "") == 0 || ft_strcmp(*line, "\n") == 0)
		cmd_rm_last();
}

int		get_next_line(char **line)
{
	int				ret;
	struct termios	term;

	ret = 1;
	init_gnl(line);
	if (!(*line && *line[0] == '\n'))
		while (g_all.arrow != 0 && g_all.ctrl_c == 0)
		{
			g_all.arrow = 0;
			if (!*line)
				*line = keep_printable(recurs(0, &ret, 0));
			else
				*line = ft_strjoin(*line, keep_printable(recurs(0, &ret, 0)));
			if (g_all.str)
				*line = ft_strjoin(g_all.str, *line);
			if (g_all.str)
				g_all.str = NULL;
			if_arrow(line);
		}
	end_gnl(line);
	tcgetattr(0, &term);
	term.c_lflag ENABLE_CANON (ICANON);
	tcsetattr(0, 0, &term);
	return (ret);
}
