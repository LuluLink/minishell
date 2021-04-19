/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 20:27:20 by macbookpro        #+#    #+#             */
/*   Updated: 2021/04/19 16:53:46 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*take_slash(char **str, int index)
{
	char	*arg;
	int		i;

	i = 0;
	arg = ft_strdup("");
	while (str && str[i] && index >= 0)
	{
		arg = ft_strjoin(arg, str[i]);
		arg = ft_strjoin(arg, ft_strdup("/"));
		i++;
		index--;
	}
	return (arg);
}

int		check_extremity(char *str, char *name)
{
	int i;
	int j;

	i = -1;
	while (str[++i] && str[i] != '*')
		if (str[i] != name[i])
			return (0);
	i = ft_strlen(str) - 1;
	if (str[i] != '*')
	{
		j = ft_strlen(name) - 1;
		while (str[i] != '*' && j >= 0 && i >= 0)
		{
			if (str[i--] != name[j--])
				return (0);
		}
	}
	return (1);
}

int		check_asterix(char *str, char *name)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (str[i])
	{
		k = 0;
		while (str[i + k] && str[i + k] != '*')
		{
			while (name[j + k] && str[i + k] != name[j + k])
				j++;
			if (str[i + k] == name[j + k])
				k++;
			else
				return (0);
		}
		i += k;
		j += k;
		if (k == 0)
			i++;
	}
	return (check_extremity(str, name));
}

void	aff_dir(char **mytab, char *str, char *name, int index)
{
	struct dirent	*lecture;
	DIR				*rep;

	if (index > 0)
		str = ft_strjoin(str, ft_strdup("/"));
	if ((mytab[index] && is_asterix(mytab[index])) || !mytab[index])
		str = ft_strjoin(str, ft_strdup(name));
	else if (mytab[index])
		str = ft_strjoin(str, ft_strdup(mytab[index]));
	rep = opendir(str);
	if (mytab && ((!is_asterix(mytab[0]) && mytab[index] && !mytab[index + 1])
	|| (is_asterix(mytab[0]) && !mytab[index])))
		insertion_end_wild(ft_strdup(str));
	while (rep && (lecture = readdir(rep)))
		if (lecture->d_name[0] != '.')
			if (mytab && mytab[index])
				if (!is_asterix(mytab[index]) || (is_asterix(mytab[index]) &&
				check_asterix(mytab[index], lecture->d_name)))
					aff_dir(mytab, ft_strdup(str),
					ft_strdup(lecture->d_name), index + 1);
	free(str);
	free(name);
	str = NULL;
	if (rep)
		closedir(rep);
}

int		is_asterix(char *str)
{
	int i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '*' && check_backslash(str, i))
			return (1);
		i++;
	}
	return (0);
}
