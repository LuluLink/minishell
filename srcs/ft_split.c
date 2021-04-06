/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2021/04/01 17:10:56 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char			**ft_free(char **mytab, int i)
{
	while (--i)
	{
		free(mytab[i]);
		mytab[i] = 0;
	}
	free(mytab[i]);
	free(mytab);
	mytab = 0;
	return (NULL);
}

static int			ft_taillem(const char *str, int i, char charset)
{
	int j;

	j = 0;
	while (str[i] != charset && str[i] != '\0')
	{
		i++;
		j++;
	}
	return (j);
}

static int			ft_nbr_mots(const char *str, char charset)
{
	int i;
	int nbr_mots;

	i = 0;
	nbr_mots = 0;
	while (str[i])
	{
		while (str[i] == charset)
			i++;
		if (str[i])
			nbr_mots++;
		while (str[i] != charset && str[i] != '\0')
			i++;
	}
	return (nbr_mots);
}

char				**ft_split(char *str, char c)
{
	int			is;
	int			i;
	int			j;
	char		**mytab;

	if (!str)
		return (NULL);
	is = 0;
	if (!(mytab = malloc(sizeof(char*) * (ft_nbr_mots(str, c) + 1))))
		return (0);
	i = 0;
	while (i < ft_nbr_mots(str, c))
	{
		j = 0;
		while (str[is] == c && str[is])
			is++;
		if (!(mytab[i] = malloc(sizeof(char) * (ft_taillem(str, is, c) + 1))))
			return (ft_free(mytab, i));
		while (str[is] != c && str[is])
			mytab[i][j++] = str[is++];
		mytab[i++][j] = '\0';
	}
	mytab[i] = NULL;
	return (mytab);
}
