/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 15:41:44 by macbookpro        #+#    #+#             */
/*   Updated: 2021/04/07 15:41:45 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
