/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2021/04/15 18:24:14 by macbookpro       ###   ########.fr       */
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

void	pwd_env2(char *str)
{
	t_elem_env	*tmp;

	tmp = g_all.first_env;
	while (tmp->next && ft_strncmp(tmp->env, "PWD=", 4) != 0)
		tmp = tmp->next;
	if (ft_strncmp(tmp->env, "PWD=", 4) == 0 && str)
	{
		ft_old_pwd(tmp->env);
		if (tmp->env[ft_strlen(tmp->env) - 1] != '/')
			tmp->env = ft_strjoin(tmp->env, ft_strdup("/"));
		tmp->env = ft_strjoin(tmp->env, ft_strdup(str));
	}
}

void	modif_pwd(char *path)
{
	int i;

	i = 0;
	if (!path)
		return ;
	while (path[i])
	{
		if (path[i] && path[i] == '.')
		{
			i++;
			if (path[i] && path[i] == '/')
				i++;
		}
		if (path[i] && path[i] != '.')
			return ;
	}
	pwd_env2(path);
}

int		ft_cd(char *path)
{
	int		i;
	int		tofree;
	char	*str;

	tofree = 0;
	if (!path)
	{
		tofree = 1;
		path = chrenv(ft_strdup("HOME"));
	}
	i = chdir(path);
	if (!(str = getcwd(NULL, 0)) || i == -1)
	{
		ft_cd2(str, strerror(errno), tofree, path);
		return (1);
	}
	pwd_env();
	if (tofree == 1)
		free(path);
	if (str)
		free(str);
	return (0);
}
