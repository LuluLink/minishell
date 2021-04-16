/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 18:23:22 by macbookpro        #+#    #+#             */
/*   Updated: 2021/04/16 19:37:22 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		check_old(void)
{
	char	*str;
	int		i;

	i = 0;
	str = chrenv(ft_strdup("OLDPWD"));
	if (str[0])
		i = chdir(str);
	else
		ft_putstr_fd("Minishell: cd: OLDPWD not set\n", 2);
	return (i);
}

int		ft_cd2(char *str, char *error, int tofree, char *path)
{
	if (!str)
	{
		ft_putstr_fd("cd: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
		ft_putstr_fd(error, 2);
		ft_putstr_fd("\n", 2);
	}
	if (g_all.err_tmp)
	{
		if (path[0] == '-' && path[1])
		{
			ft_putstr_fd("bash: cd: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": invalid option\ncd: usage: cd [-L|-P] [dir]", 2);
		}
		else
			ft_putstr_fd(error, 2);
		ft_putstr_fd("\n", 2);
		g_all.err_tmp = NULL;
	}
	modif_pwd(path);
	cd_free(tofree, path, str);
	return (1);
}

void	cd_free(int tofree, char *path, char *str)
{
	if (tofree == 1)
		free(path);
	if (str)
		free(str);
}
