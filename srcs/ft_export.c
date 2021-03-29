/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2021/03/28 11:03:38 by pacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			remplace_env(char *str)
{
	int			i;
	t_elem_env	*tmp;

	i = 0;
	tmp = g_all.first_env;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	while (tmp != NULL)
	{
		if ((ft_strncmp(tmp->env, str, i) == 0))
		{
			free(tmp->env);
			tmp->env = str;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int			count_without_quote(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
		{
			i++;
			while (str[i] != '\"' && str[i] != '\0')
			{
				i++;
				j++;
			}
			i++;
		}
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'' && str[i] != '\0')
			{
				i++;
				j++;
			}
			i++;
		}
		if (str[i] != '\0')
		{
			j++;
			i++;
		}
	}
	return (j);
}

char		*str_to_env(char *str)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = count_without_quote(str);
	dest = malloc(sizeof(char) * (j + 1));
	dest[j] = '\0';
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
		{
			i++;
			while (str[i] != '\"' && str[i] != '\0')
				dest[j++] = str[i++];
			i++;
		}
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'' && str[i] != '\0')
				dest[j++] = str[i++];
			i++;
		}
		if (str[i] != '\0')
			dest[j++] = str[i++];
	}
	return (dest);
}

int			verif_arg_export(t_elem_cmd *actual)
{
	int			i;
	t_elem_cmd	*tmp;

	i = 0;
	tmp = actual->next;
	while (tmp->cmd[i] != '\0' && tmp->cmd[i] != '=')
	{
		if ((tmp->cmd[i] >= '0' && tmp->cmd[i] <= '9') && i == 0)
			return (-1);
		if (tmp->cmd[i] < '0' || tmp->cmd[i] > 'z')
			return (-1);
		if (tmp->cmd[i] > '9' && tmp->cmd[i] < 'A')
			return (-1);
		if ((tmp->cmd[i] > 'Z' && tmp->cmd[i] < '_') || tmp->cmd[i] == '`')
			return (-1);
		if (tmp->cmd[i] == '\"')
		{
			i++;
			if (tmp->cmd[i] == '\0' || tmp->cmd[i] == '=')
				return (0);
		}
		i++;
	}
	return (0);
}

void		ft_sort_lst(t_elem_env *lst)
{
	t_elem_env	*first;
	char		*tmp;

	first = lst;
	while (first && first->next)
	{
		if (ft_strcmp(first->env, first->next->env) > 0)
		{
			tmp = first->env;
			first->env = first->next->env;
			first->next->env = tmp;
			first = lst;
		}
		else
			first = first->next;
	}
}

t_elem_env	*ft_copy_sort(t_elem_env *tocopy)
{
	t_elem_env	*first;
	t_elem_env	*new;
	t_elem_env	*tmp;

	first = NULL;
	tmp = NULL;
	while (tocopy)
	{
		new = malloc(sizeof(t_elem_env));
		new->env = ft_strdup(tocopy->env);
		if (tmp)
			tmp->next = new;
		tmp = new;
		if (!first)
			first = new;
		tocopy = tocopy->next;
	}
	tmp->next = NULL;
	ft_sort_lst(first);
	return (first);
}

void		ft_export(t_elem_cmd *actual)
{
	int			i;
	int			verif_quote;
	char		*str;
	t_elem_env	*tmp;
	t_elem_env	*first;

	i = 0;
	verif_quote = 0;
	if (actual->next == NULL || actual->next->token != ARG)
	{
		first = ft_copy_sort(g_all.first_env);
		tmp = first;
		while (tmp != NULL)
		{
			ft_putstr("declare -x ");
			while (tmp->env[i] != '\0')
			{
				ft_putchar(tmp->env[i]);
				if (tmp->env[i] == '=' && verif_quote == 0)
				{
					ft_putchar('\"');
					verif_quote = 1;
				}
				if (tmp->env[i + 1] == '\0' && verif_quote == 1)
					ft_putchar('\"');
				i++;
			}
			i = 0;
			verif_quote = 0;
			tmp = tmp->next;
			ft_putchar('\n');
		}
		free_list_env_sort(first);
		return ;
	}
	while (actual->next != NULL && actual->next->token == ARG)
	{
		if ((verif_arg_export(actual) == 0))
		{
			str = str_to_env(actual->next->cmd);
			if ((remplace_env(str) == 0))
				insertion_end_env(str);
		}
		else
			printf("export : %s : indentifiant invalide\n", actual->next->cmd);
		actual = actual->next;
	}
}
