/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2021/03/28 11:03:38 by pacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_env()
{
	int			verif;
	int			i;
    t_elem_env	*tmp;

	tmp = g_all.first_env;
	verif = 0;
	i = 0;
	while (tmp != NULL)
	{
		while (tmp->env[i] != '\0')
		{
			if (tmp->env[i] == '=')
				verif = 1;
			i++;
		}
		if (verif == 1)
		{
			ft_putstr(tmp->env);
			ft_putchar('\n');
		}
		i = 0;
		verif = 0;
		tmp = tmp->next;
	}
}