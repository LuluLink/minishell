/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2021/04/07 15:22:05 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			print_env(t_elem_env *tmp, int i, int verif_quote)
{
	ft_putchar(tmp->env[i]);
	if (tmp->env[i] == '=' && verif_quote == 0)
	{
		ft_putchar('\"');
		verif_quote = 1;
	}
	if (tmp->env[i + 1] == '\0' && verif_quote == 1)
		ft_putchar('\"');
	return (verif_quote);
}

int			remplace_env(char *str)
{
	int			i;
	t_elem_env	*tmp;

	i = 0;
	tmp = g_all.first_env;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	while (tmp != NULL)
	{
		if ((ft_strncmp(tmp->env, str, i) == 0))
		{
			free(tmp->env);
			tmp->env = str;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
