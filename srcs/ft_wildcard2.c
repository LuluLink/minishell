/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 20:29:28 by macbookpro        #+#    #+#             */
/*   Updated: 2021/04/19 16:59:28 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*modif_str(char *str)
{
	char *str2;

	str2 = ft_strdup(&str[2]);
	free(str);
	return (str2);
}

void	insertion_end_wild(char *str)
{
	t_elem_cmd *nouveau;
	t_elem_cmd *tmp;

	nouveau = malloc(sizeof(t_elem_cmd));
	if (ft_strncmp(str, "./", 2) == 0)
		str = modif_str(str);
	tmp = g_all.wildcard;
	if (tmp == NULL)
	{
		free(nouveau);
		initialisation_wild(str, ARG);
		return ;
	}
	nouveau->cmd = str;
	nouveau->token = ARG;
	if (tmp->next == NULL)
	{
		tmp->next = nouveau;
		nouveau->next = NULL;
		nouveau->prev = g_all.wildcard;
		return ;
	}
	ft_add_back(tmp, nouveau);
}

void	ft_list_sort(t_elem_cmd **begin_list, int (*cmp)())
{
	t_elem_cmd	*curr;
	t_elem_cmd	*next;
	void		*tmp;

	curr = *begin_list;
	if (curr == NULL || curr->next == NULL)
		return ;
	while (curr->next)
	{
		next = curr->next;
		if ((*cmp)(curr->cmd, next->cmd) > 0)
		{
			tmp = curr->cmd;
			curr->cmd = next->cmd;
			next->cmd = tmp;
			curr = *begin_list;
		}
		else
			curr = curr->next;
	}
}

void	last_wc(t_elem_cmd *next)
{
	t_elem_cmd	*tmp;

	tmp = g_all.wildcard;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = next;
}
