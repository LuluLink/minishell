/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_backslash.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2021/04/13 12:58:51 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_bs_alone(void)
{
	t_elem_cmd *actuel;

	actuel = g_all.first_cmd;
	while (actuel)
	{
		if (ft_strcmp(actuel->cmd, "\\") == 0)
		{
			free(actuel->cmd);
			actuel->cmd = ft_strdup("\\ ");
		}
		actuel = actuel->next;
	}
}

char	*insert_backslash(char *line, int i)
{
	int		j;
	char	*dest;

	j = ft_strlen(line);
	dest = malloc(sizeof(char) * (j + 2));
	dest[j + 1] = '\0';
	j = 0;
	while (j > i)
	{
		dest[j] = line[j];
		j++;
	}
	dest[j] = '\'';
	dest[j + 1] = line[i + 1];
	dest[j + 2] = '\'';
	j = j + 3;
	i = i + 2;
	while (line[i] != '\0')
	{
		dest[j] = line[i];
		j++;
		i++;
	}
	free(line);
	return (dest);
}
