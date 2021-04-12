/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_histo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 15:40:57 by macbookpro        #+#    #+#             */
/*   Updated: 2021/04/12 17:19:36 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_aff_index(void)
{
	char		*cl_cap;
	t_elem_env	*tmp;
	int			i;

	i = 0;
	tmp = g_all.cmd_lst;
	while (tmp && i++ < g_all.index)
		tmp = tmp->next;
	tputs(tgetstr("cr", NULL), 1, ft_mypc);
	cl_cap = tgetstr("up", NULL);
	while (g_all.cursor_x > g_all.term_x)
	{
		g_all.cursor_x -= g_all.term_x;
		tputs(cl_cap, 1, ft_mypc);
	}
	cl_cap = tgetstr("cd", NULL);
	tputs(cl_cap, 1, ft_mypc);
	write(1, NEWLINE, ft_strlen(NEWLINE));
	write(1, tmp->env, ft_strlen(tmp->env));
	g_all.cursor = ft_strlen(tmp->env);
	g_all.cursor_x = g_all.cursor + 3;
	if (g_all.str)
		free(g_all.str);
	g_all.str = ft_strdup(tmp->env);
}

void	cmd_histo(void)
{
	if (g_all.arrow == 1)
	{
		g_all.index = (g_all.index > 0) ? g_all.index - 1 : g_all.index;
		ft_aff_index();
	}
	else if (g_all.arrow == 2)
	{
		g_all.index = (g_all.index < lst_len() - 1) ? g_all.index + 1
		: lst_len() - 1;
		ft_aff_index();
	}
}

/*
** g_all.arrow 1 -> fleche du haut
**             2 -> fleche du bas
**             3 -> del
*/

void	rm_del2(void)
{
	tputs(tgetstr("le", NULL), 1, ft_mypc);
	tputs(tgetstr("le", NULL), 1, ft_mypc);
	tputs(tgetstr("cd", NULL), 1, ft_mypc);
}

void	rm_del(char *a)
{
	a[0] = '\n';
	g_all.arrow = 3;
	if (g_all.cursor > 0)
	{
		if (g_all.cursor_x % g_all.term_x == 0 ||
		g_all.cursor_x % g_all.term_x == g_all.term_x - 1)
		{
			tputs(tgetstr("up", NULL), 1, ft_mypc);
			tputs(tgoto(tgetstr("ch", NULL), g_all.cursor_x,
			g_all.cursor_x), 1, ft_mypc);
			if (g_all.cursor_x % g_all.term_x == g_all.term_x - 1)
				tputs(tgetstr("le", NULL), 1, ft_mypc);
			tputs(tgetstr("cd", NULL), 1, ft_mypc);
			g_all.cursor = (g_all.cursor > 0) ? g_all.cursor - 1 : g_all.cursor;
			g_all.cursor_x = (g_all.cursor_x > 0) ?
			g_all.cursor_x - 1 : g_all.cursor_x;
			return ;
		}
		else if (g_all.cursor_x % g_all.term_x != g_all.term_x - 2)
			tputs(tgetstr("le", NULL), 1, ft_mypc);
	}
	rm_del2();
	g_all.cursor = (g_all.cursor > 0) ? g_all.cursor - 1 : g_all.cursor;
	g_all.cursor_x = (g_all.cursor_x > 0) ? g_all.cursor_x - 1 : g_all.cursor_x;
}

void	check_arrow(char *a)
{
	static int i;

	if (a[0] == 127)
		rm_del(a);
	else if (i == 0 && a[0] == 27)
	{
		i = 1;
		g_all.cursor_x += 2;
	}
	else if (i == 1 && a[0] == '[')
		i = (++g_all.cursor_x) ? 2 : 2;
	else if (i == 2 && (a[0] == 'A' || a[0] == 'B'))
	{
		g_all.arrow = a[0] - 64;
		i = (++g_all.cursor_x) ? 0 : 0;
		a[0] = '\n';
	}
	else
	{
		i = 0;
		g_all.cursor++;
		g_all.cursor_x++;
	}
}
