/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 15:41:36 by macbookpro        #+#    #+#             */
/*   Updated: 2021/04/07 15:41:37 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		len_value(char *str)
{
	int i;
	int j;
	int verif;

	i = 0;
	j = 0;
	verif = 0;
	while (str[i] != '\0')
	{
		if (verif == 1)
			j++;
		if (str[i] == '=' && verif == 0)
			verif = 1;
		i++;
	}
	return (j);
}

char	*fill_with_env_value(int i, char *str)
{
	char	*tmp;
	int		j;
	int		verif;

	j = 0;
	verif = 0;
	tmp = malloc(sizeof(char) * (i + 1));
	tmp[i] = '\0';
	i = 0;
	while (str[i] != '\0')
	{
		if (verif == 1)
		{
			tmp[j] = str[i];
			j++;
		}
		if (str[i] == '=' && verif == 0)
			verif = 1;
		i++;
	}
	return (tmp);
}

char	*first_is_nbr(char *str)
{
	int		i;
	int		j;
	char	*dest;

	j = 1;
	i = ft_strlen(str) - 1;
	dest = malloc(sizeof(char) * i + 1);
	dest[i] = '\0';
	i = 0;
	while (dest[i] != '\0')
	{
		dest[i] = str[j];
		i++;
		j++;
	}
	return (dest);
}

char	*chrenv(char *str)
{
	int			i;
	int			size;
	char		*dest;
	t_elem_env	*tmp;

	i = 0;
	tmp = g_all.first_env;
	dest = NULL;
	size = ft_strlen(str);
	if	((ft_strncmp("?", str, size) == 0))
		dest = ft_itoa(g_all.exit_code);
	while (tmp != NULL && dest == NULL)
	{
		if ((ft_strncmp(tmp->env, str, size) == 0))
		{
			i = len_value(tmp->env);
			dest = fill_with_env_value(i, tmp->env);
			free(str);
			return (dest);
		}
		tmp = tmp->next;
	}
	if (str[0] >= '0' && str[0] <= '9')
		dest = first_is_nbr(str);
	free(str);
	return (dest);
}
