/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2021/04/07 15:41:11 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_old_pwd(char *str)
{
	t_elem_env *tmp;

	tmp = g_all.first_env;
	while (tmp->next && ft_strncmp(tmp->env, "OLDPWD=", 7) != 0)
		tmp = tmp->next;
	if (ft_strncmp(tmp->env, "OLDPWD=", 7) == 0)
	{
		free(tmp->env);
		tmp->env = ft_strjoin(ft_strdup("OLD"), ft_strdup(str));
	}
}

void	pwd_env(void)
{
	t_elem_env	*tmp;
	char		*pwd;

	pwd = getcwd(NULL, 0);
	tmp = g_all.first_env;
	while (tmp->next && ft_strncmp(tmp->env, "PWD=", 4) != 0)
		tmp = tmp->next;
	if (ft_strncmp(tmp->env, "PWD=", 4) == 0 && pwd)
	{
		ft_old_pwd(tmp->env);
		free(tmp->env);
		tmp->env = ft_strjoin(ft_strdup("PWD="), ft_strdup(pwd));
	}
	if (pwd)
		free(pwd);
}

int		ft_cd(char *path)
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
		return (1);
	}
	pwd_env();
	if (tofree == 1)
		free(path);
	return (0);
}
