/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2021/04/15 16:06:39 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		check_path_cmd(char *path)
{
	int fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

char	*check_cmd(t_elem_cmd *tmp)
{
	char	*path;
	char	**files;
	char	*cmd;
	int		i;

	if (!(path = chrenv(ft_strdup("PATH"))))
		path = ft_strdup("");
	files = ft_split(path, ':');
	i = 0;
	while (files[i])
	{
		files[i] = ft_strjoin(files[i],
		ft_strjoin(ft_strdup("/"), ft_strdup(tmp->cmd)));
		if (check_path_cmd(files[i]))
		{
			cmd = ft_strdup(files[i]);
			free_double_char(files);
			free(path);
			return (cmd);
		}
		i++;
	}
	free_double_char(files);
	free(path);
	return (NULL);
}
