/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2021/04/07 15:22:05 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void		inc_i_j(void)
{
	g_all.i++;
	g_all.j++;
}

int			count_without_quote(char *str)
{
	g_all.i = 0;
	g_all.j = 0;
	while (str[g_all.i] != '\0')
	{
		if (str[g_all.i] == '\"')
		{
			g_all.i++;
			while (str[g_all.i] != '\"' && str[g_all.i] != '\0')
				inc_i_j();
			g_all.i++;
		}
		if (str[g_all.i] == '\'')
		{
			g_all.i++;
			while (str[g_all.i] != '\'' && str[g_all.i] != '\0')
				inc_i_j();
			g_all.i++;
		}
		if (str[g_all.i] != '\0')
			inc_i_j();
	}
	return (g_all.j);
}

char		*init_dest(char *str)
{
	int		j;
	char	*tmp;

	j = count_without_quote(str);
	tmp = malloc(sizeof(char) * (j + 1));
	tmp[j] = '\0';
	return (tmp);
}

char		*copy_without_quote(char *str, char *dest)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
		{
			i++;
			while (str[i] != '\"' && str[i] != '\0')
				dest[j++] = str[i++];
			i++;
		}
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'' && str[i] != '\0')
				dest[j++] = str[i++];
			i++;
		}
		if (str[i] != '\0')
			dest[j++] = str[i++];
	}
	return (dest);
}

char		*str_to_env(char *str)
{
	char	*dest;

	dest = init_dest(str);
	dest = copy_without_quote(str, dest);
	return (dest);
}
