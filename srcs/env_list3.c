/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2021/04/07 15:41:06 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_list_env_sort(t_elem_env *lst)
{
	t_elem_env *tmp;

	tmp = lst;
	while (tmp)
	{
		free(tmp->env);
		lst = lst->next;
		free(tmp);
		tmp = lst;
	}
}

void	free_list_env(void)
{
	t_elem_env *tmp;

	tmp = g_all.first_env;
	while (tmp != NULL)
	{
		free(tmp->env);
		g_all.first_env = g_all.first_env->next;
		free(tmp);
		tmp = g_all.first_env;
	}
}
