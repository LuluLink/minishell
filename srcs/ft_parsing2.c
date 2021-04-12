/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 16:24:17 by macbookpro        #+#    #+#             */
/*   Updated: 2021/04/12 11:40:32 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		check_backslash(char *str, int i)
{
	int ischar;

	ischar = 1;
	while (--i >= 0 && str[i] == '\\')
	{
		if (ischar == 0)
			ischar = 1;
		else
			ischar = 0;
	}
	return (ischar);
}

int		check_last(void)
{
	t_elem_cmd *tmp;

	tmp = g_all.first_cmd;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
	{
		if (tmp->token == ARG)
		{
			printf("Syntax error : '%s'\n", tmp->cmd);
			free_list_cmd();
			return (1);
		}
	}
	return (0);
}

char	*check_dollar_next(int quote, char *str, int *i, char *str2)
{
	int		j;

	j = 0;
	while (str[i[0] + j] && (str[i[0] + j] != '$' || quote == 1))
	{
		if (str[i[0] + j] == '\'' && check_backslash(str, i[0] + j)
		&& quote != 2)
			quote = (quote == 0) ? 1 : 0;
		if (str[i[0] + j] == '\"' && check_backslash(str, i[0] + j)
		&& quote != 1)
			quote = (quote == 0) ? 2 : 0;
		j++;
	}
	str2 = ft_strjoin(str2, ft_strndup(&str[i[0]], j));
	i[0] += j;
	j = 1;
	if (str[i[0]] == '$' && quote != 1 && check_backslash(str, i[0]))
	{
		while (str[i[0] + j] && (ft_isalnum(str[i[0] + j]) || str[i[0]
		+ j] == '_' || str[i[0] == '?']) && !(j >= 2 && str[i[0] + 1] == '?'))
			j++;
		str2 = ft_strjoin(str2, chrenv(ft_strndup(&str[i[0] + 1], j - 1)));
		i[0] += j;
	}
	return (str2);
}

char	*check_dollar(char *str)
{
	int		i;
	int		quote;
	char	*str2;

	i = 0;
	quote = 0;
	str2 = ft_strdup("");
	while (str[i])
		str2 = check_dollar_next(quote, str, &i, str2);
	free(str);
	return (str2);
}
