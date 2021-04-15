/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2021/04/13 16:58:35 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			verif_arg_export(t_elem_cmd *actual)
{
	int			i;
	t_elem_cmd	*tmp;

	i = 0;
	tmp = actual->next;
	if (tmp->cmd[0] == '=')
		return (-1);
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
			if (tmp->cmd[++i] == '\0' || tmp->cmd[i] == '=')
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

int			export_no_arg(void)
{
	int			i;
	int			verif_quote;
	t_elem_env	*tmp;
	t_elem_env	*first;

	i = 0;
	verif_quote = 0;
	first = ft_copy_sort(g_all.first_env);
	tmp = first;
	while (tmp != NULL)
	{
		ft_putstr("declare -x ");
		while (tmp->env[i] != '\0')
		{
			verif_quote = print_env(tmp, i, verif_quote);
			i++;
		}
		i = 0;
		verif_quote = 0;
		tmp = tmp->next;
		ft_putchar('\n');
	}
	free_list_env_sort(first);
	return (0);
}

int			ft_export(t_elem_cmd *actual)
{
	int			ret;
	char		*str;

	ret = 0;
	if (actual->next == NULL || actual->next->token != ARG)
		return (export_no_arg());
	while (actual->next != NULL && actual->next->token == ARG)
	{
		if ((verif_arg_export(actual) == 0))
		{
			str = str_to_env(actual->next->cmd);
			if ((remplace_env(str) == 0))
				insertion_end_env(str);
		}
		else
		{
			print_error_export(actual->next->cmd);
			ret = 1;
		}
		actual = actual->next;
	}
	if (ret == 1)
		return (1);
	return (0);
}
