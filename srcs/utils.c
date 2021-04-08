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

int			ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
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
