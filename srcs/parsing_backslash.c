/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_backslash.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2021/03/28 11:03:38 by pacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
