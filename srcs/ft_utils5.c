/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 15:34:23 by macbookpro        #+#    #+#             */
/*   Updated: 2021/04/14 16:26:56 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	reset_var(void)
{
	g_all.child = 0;
	g_all.dad = 0;
	g_all.block_cmd = 0;
	g_all.in_loop = 0;
}

void	check_multiple_words(t_elem_cmd *tmp)
{
	t_elem_cmd	*last;
	t_elem_cmd	*prev;
	char		**mytab;
	int			i;

	i = 0;
	mytab = ft_split(tmp->cmd, ' ');
	free(tmp->cmd);
	tmp->cmd = mytab[i];
	last = tmp->next;
	while (mytab[++i])
	{
		tmp->next = malloc(sizeof(t_elem_cmd));
		prev = tmp;
		tmp = tmp->next;
		tmp->prev = prev;
		tmp->cmd = mytab[i];
		search_token(tmp->cmd, tmp, prev);
	}
	tmp->next = last;
	free(mytab);
}

int		ft_is_token(int i)
{
	if (i == RIGHT || i == DOUBLERIGHT || i ==
		LEFT || i == PIPE || i == SEMICOLON)
		return (1);
	return (0);
}

int		ft_check_sep(void)
{
	t_elem_cmd	*tmp;

	tmp = g_all.first_cmd;
	while (tmp)
	{
		if (ft_is_token(tmp->token))
			if (!tmp->prev || (!tmp->next && tmp->token != SEMICOLON) ||
			(tmp->next && ft_is_token(tmp->next->token)))
			{
				g_all.exit_code = 2;
				ft_putstr_fd("Minishell: syntax error near unexpected \
token `", 2);
				ft_putstr_fd(tmp->cmd, 2);
				ft_putstr_fd("'\n", 2);
				return (0);
			}
		tmp = tmp->next;
	}
	return (1);
}
