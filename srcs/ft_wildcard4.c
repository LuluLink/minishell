/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 16:56:39 by macbookpro        #+#    #+#             */
/*   Updated: 2021/04/19 17:34:44 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_wild2(t_elem_cmd **tmp, t_elem_cmd **prev, t_elem_cmd **next)
{
	g_all.wildcard = NULL;
	is_wildcard(ft_strdup((*tmp)->cmd));
	ft_list_sort(&g_all.wildcard, &ft_strcmp);
	if (g_all.wildcard)
	{
		(*prev)->next = g_all.wildcard;
		last_wc(*next);
		free((*tmp)->cmd);
		free(*tmp);
		*prev = *tmp;
		*tmp = g_all.first_cmd;
	}
	else
	{
		*prev = *tmp;
		*tmp = (*tmp)->next;
		if (*tmp)
			*next = (*tmp)->next;
	}
}

void	check_wild(void)
{
	t_elem_cmd	*tmp;
	t_elem_cmd	*prev;
	t_elem_cmd	*next;

	tmp = g_all.first_cmd;
	prev = tmp;
	next = tmp->next;
	while (tmp && tmp->cmd)
	{
		if (tmp->cmd && tmp->token == ARG && tmp->cmd[0] != '\"' && tmp->cmd[0]
		!= '\'' && is_asterix(tmp->cmd))
			check_wild2(&tmp, &prev, &next);
		else
		{
			prev = tmp;
			tmp = tmp->next;
			if (tmp)
				next = tmp->next;
		}
	}
}
