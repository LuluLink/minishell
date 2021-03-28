/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2021/03/28 11:03:38 by pacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_env(char *str)
{
	t_elem_env *tmp;

	tmp = g_all.first_env;
	while (tmp->next && ft_strncmp(tmp->env, "PWD=", 4) == 0)
		tmp = tmp->next;
	if (ft_strncmp(tmp->env, "PWD=", 4) == 0)
	{
		free(tmp->env);
		tmp->env = ft_strjoin(ft_strdup("PWD="), str);
	}
}

void	ft_cd(char *path)
{
	char	*error;
	int		tofree;

	tofree = 0;
	if (!path)
	{
		tofree = 1;
		path = chrenv(ft_strdup("HOME"));
	}
	if (chdir(path) == -1)
	{
		error = strerror(errno);
		ft_putstr_fd(error, 2);
		ft_putstr_fd("\n", 2);
		if (tofree == 1)
			free(path);
		return ;
	}
	pwd_env(path);
	if (tofree == 1)
		free(path);
}
