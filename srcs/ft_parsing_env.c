/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 15:41:36 by macbookpro        #+#    #+#             */
/*   Updated: 2021/04/13 13:06:13 by macbookpro       ###   ########.fr       */
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
	int		tmp;
	char	*dest;

	j = 1;
	i = ft_strlen(str) - 1;
	tmp = i;
	dest = malloc(sizeof(char) * (i + 1));
	dest[i] = '\0';
	i = 0;
	while (i <= tmp)
	{
		dest[i] = str[j];
		i++;
		j++;
	}
	return (dest);
}

char	*verif_dest_null(char *dest)
{
	if (dest == NULL)
		return (ft_strdup(""));
	return (dest);
}

char	*chrenv(char *str)
{
	int			size;
	char		*dest;
	t_elem_env	*tmp;

	tmp = g_all.first_env;
	dest = NULL;
	size = ft_strlen(str);
	if ((ft_strncmp("?", str, size) == 0))
		dest = ft_itoa(g_all.exit_code);
	while (tmp && !dest)
	{
		if ((ft_strncmp(tmp->env, str, size) == 0))
		{
			dest = fill_with_env_value(len_value(tmp->env), tmp->env);
			free(str);
			return (dest);
		}
		tmp = tmp->next;
	}
	dest = (str[0] >= '0' && str[0] <= '9') ? first_is_nbr(str) : dest;
	free(str);
	dest = verif_dest_null(dest);
	return (dest);
}
