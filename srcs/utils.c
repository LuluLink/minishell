/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 15:41:44 by macbookpro        #+#    #+#             */
/*   Updated: 2021/04/07 15:41:45 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int			ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int			ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char		*ft_strndup(const char *src, int n)
{
	int		i;
	char	*dest;

	i = 0;
	if (!(dest = (char *)malloc(sizeof(char) *
	(((ft_strlen(src) > n) ? n : ft_strlen(src)) + 1))))
		return (0);
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int			ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0' && i < n - 1)
		i++;
	return (s1[i] - s2[i]);
}

char		*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	j = 0;
	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(str = malloc(sizeof(char) * i)))
		return (NULL);
	i = 0;
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	free(s1);
	free(s2);
	return (str);
}

char		*ft_strdup(const char *src)
{
	char	*dest;
	int		i;

	i = 0;
	while (src[i])
		i++;
	dest = malloc(sizeof(*dest) * i + 1);
	i = 0;
	if (dest == NULL)
		return (0);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char		*ft_strnjoin(char *s1, char *s2, int n)
{
	int		i;
	int		j;
	char	*str;

	j = 0;
	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1) + ((ft_strlen(s2) > n) ? n : ft_strlen(s2)) + 1;
	if (!(str = malloc(sizeof(char) * i)))
		return (NULL);
	i = 0;
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i] && n-- > 0)
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}

char		*ft_strjoinchar(char *s1, char s2)
{
	int		i;
	int		j;
	char	*str;

	j = 0;
	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1) + 2;
	if (!(str = malloc(sizeof(char) * i)))
		return (NULL);
	i = 0;
	while (s1[i])
		str[j++] = s1[i++];
	str[j++] = s2;
	str[j] = '\0';
	free(s1);
	return (str);
}

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
		write(2, COLOREND, ft_strlen(COLOREND));
}

int			ft_isalnum(int c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') ||
			(c >= 'A' && c <= 'Z'));
}

void		free_double_char(char **str)
{
	int i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	if (str)
		free(str);
}

void		ft_aff_minishell(void)
{
	printf("\n                                  __              \
___    ___      \n /'\\_/`\\  __          __         /\\ \\            \
/\\_ \\  /\\_ \\     \n/\\      \\/\\_\\    ___ /\\_\\    ____\\ \\ \\___      \
__\\//\\ \\ \\//\\ \\    \n\\ \\ \\__\\ \\/\\ \\ /' _ `\\/\\ \\  /',__\\\\ \\  \
_ `\\  /'__`\\\\ \\ \\  \\ \\ \\   \n \\ \\ \\_/\\ \
\\ \\ \\/\\ \\/\\ \\ \\ \\/\\__, \
`\\\\ \\ \\ \\ \\/\\  __/ \\_\\ \\_ \\_\\ \\_ \
\n  \\ \\_\\\\ \\_\\ \\_\\ \\_\\ \\_\\ \
\\_\\/\\____/ \\ \\_\\ \\_\\ \\____\\/\\____\\\
/\\____\\\n   \\/_/ \\/_/\\/_/\\/_/\\/_\
/\\/_/\\/___/   \\/_/\\/_/\\/____/\\/____/\\/____/\n\n");
}

int			ft_atoi(char *str)
{
	int i;
	int tmp;
	int sign;

	i = 0;
	sign = 1;
	tmp = 0;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n' ||
		str[i] == '\r' || str[i] == '\t' || str[i] == '\v')
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		tmp = tmp * 10 + str[i++] - '0';
	return (tmp * sign);
}
