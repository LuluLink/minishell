/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 15:41:44 by macbookpro        #+#    #+#             */
/*   Updated: 2021/04/16 19:10:38 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void		ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void		ft_putstr_fd(char *s, int fd)
{
	int i;

	i = 0;
	if (!s)
		return ;
	if (fd == 2)
		write(2, STRERRORCOLOR, ft_strlen(STRERRORCOLOR));
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
	if (fd == 2)
		write(2, COLORSTART, ft_strlen(COLORSTART));
}

void		ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
}

void		ft_putchar(char c)
{
	write(1, &c, 1);
}

int			ft_isspace(int c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v' ||
	c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}
