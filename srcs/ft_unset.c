/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2021/03/28 11:03:38 by pacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(char *str)
{
	int			ret;
	t_elem_env	*tmp;


	ret = ft_strlen(str);
	tmp = g_all.first_env;
	while (tmp != NULL)
	{
		if ((ft_strncmp(tmp->env, str, ret) == 0))
		{
			suppression_middle_env(tmp);
			return ;
		}
		tmp = tmp->next;
	}
}