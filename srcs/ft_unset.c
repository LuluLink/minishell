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

int		ft_unset(t_elem_cmd *actual)
{
	int			ret;
	t_elem_env	*tmp;

	while (actual != NULL && actual->token != ARG)
	{
		ret = ft_strlen(actual->cmd);
		tmp = g_all.first_env;
		while (tmp != NULL)
		{
			if ((ft_strncmp(tmp->env, actual->cmd, ret) == 0))
			{
				suppression_middle_env(tmp);
				return (0);
			}
			tmp = tmp->next;
		}
		actual = actual->next;
	}
	return (0);
}