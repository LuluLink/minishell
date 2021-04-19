/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 16:56:31 by macbookpro        #+#    #+#             */
/*   Updated: 2021/04/19 17:34:39 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	is_wildcard(char *path)
{
	char			**mytab;
	char			*str;
	int				i;

	mytab = ft_split(path, '/');
	mytab = ft_split_slash(mytab);
	if (is_asterix(mytab[0]))
		str = ft_strdup(".");
	else
		str = ft_strdup("");
	free(path);
	aff_dir(mytab, ft_strdup(""), str, 0);
	i = 0;
	while (mytab[i])
		free(mytab[i++]);
	free(mytab);
}

char	**ft_create_split(char **str, int count)
{
	char	**mytab;
	int		i;
	int		j;

	mytab = malloc(sizeof(char*) * (count + 1));
	i = 0;
	j = 0;
	while (i < count)
	{
		mytab[i] = ft_strdup("");
		if (str[j] && is_asterix(str[j]))
			mytab[i] = ft_strjoin(mytab[i], str[j++]);
		else
			while (str[j] && !is_asterix(str[j]))
			{
				if (mytab[i][0])
					mytab[i] = ft_strjoin(mytab[i], ft_strdup("/"));
				mytab[i] = ft_strjoin(mytab[i], str[j++]);
			}
		i++;
	}
	mytab[i] = NULL;
	free(str);
	return (mytab);
}

char	**ft_split_slash(char **str)
{
	int	i;
	int	j;
	int count;

	i = 0;
	j = 0;
	count = 0;
	while (str[i])
	{
		j = i;
		while (str[i] && !is_asterix(str[i]))
			i++;
		if (i != j)
			count++;
		while (str[i] && is_asterix(str[i]))
		{
			i++;
			count++;
		}
	}
	return (ft_create_split(str, count));
}

void	initialisation_wild(char *str, int token)
{
	t_elem_cmd *cmd;

	cmd = malloc(sizeof(t_elem_cmd));
	cmd->cmd = str;
	cmd->token = token;
	cmd->next = NULL;
	cmd->prev = NULL;
	g_all.wildcard = cmd;
}
