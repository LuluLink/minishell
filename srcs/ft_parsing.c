/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 15:41:32 by macbookpro        #+#    #+#             */
/*   Updated: 2021/04/15 13:20:27 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** check_token check si le char envoyé est un tocken " ' | < > $
** si i vaut 0 il check tous les tokens
** si i vaut 1 il ne check que les separateurs
*/

int		check_token(char *str, int k, int i)
{
	int j;

	j = 0;
	if (i == 0)
		if (str[k] == '<' || str[k] == '>' || str[k] == '|' || str[k] == '\''
		|| str[k] == '\"' || str[k] == '$' || str[k] == ';')
			j = check_backslash(str, k);
	if (i == 1)
		if (str[k] == '<' || str[k] == '>' || str[k] == '|' || str[k] == ';')
			j = check_backslash(str, k);
	return (j);
}

int		ft_skipspaces(char *str)
{
	int i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (i);
}

int		pass_quote(char *str, int j)
{
	int		i;
	char	a;

	i = 0;
	if (str[i] && j == 1 && (str[i] == '\'' || str[i] == '\"'))
	{
		a = str[i];
		i++;
		while (str[i])
		{
			if (str[i] == a)
				if (check_backslash(str, i))
					break ;
			i++;
		}
		return (i + 1);
	}
	else
		return (1);
}

int		check_str(char *buff, int i)
{
	int j;

	j = 0;
	while (buff[i + j] && !check_token(buff, i + j, 1)
	&& !ft_isspace(buff[i + j]))
		j += pass_quote(&buff[i + j], check_backslash(buff, i + j));
	if (j > 0)
		insertion_end_cmd(ft_strndup(&buff[i], j), 0);
	i += j + ft_skipspaces(&buff[i + j]);
	j = 0;
	if (buff[i] && check_token(buff, i, 1))
		j = (buff[i] == '>' && buff[i + 1] == '>') ? j + 2 : j + 1;
	if (j > 0)
	{
		insertion_end_cmd(ft_strndup(&buff[i], j), 0);
		if (check_last())
			return (-1);
	}
	i += j + ft_skipspaces(&buff[i + j]);
	return (i);
}

void	start_parsing(void)
{
	int i;
	int pid;

	i = 0;
	pid = 0;
	while (g_all.buff && g_all.buff[i])
	{
		i = check_str(g_all.buff, i);
		if (i == -1)
			return ;
	}
	ft_bs_alone();
	ft_start_execution(g_all.first_cmd, pid);
}
