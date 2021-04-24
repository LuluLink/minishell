/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2021/04/16 19:35:05 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	insert_after_null(t_elem_cmd *tocopy)
{
	t_elem_cmd *tmp;

	tmp = g_all.first_cmd;
	tocopy->next = g_all.first_cmd;
	tocopy->prev = NULL;
	tmp->prev = tocopy;
	g_all.first_cmd = tocopy;
	tocopy->token = CMD;
}

void	insert_after_cmd(t_elem_cmd *tocopy, t_elem_cmd *before,
t_elem_cmd *after)
{
	tocopy->next = after;
	tocopy->prev = before;
	before->next = tocopy;
	after->prev = tocopy;
}

void	delete_arg(t_elem_cmd *todel, t_elem_cmd *after,
t_elem_cmd *before)
{
	todel->next = NULL;
	todel->prev = NULL;
	if (after != NULL)
		after->prev = before;
	before->next = after;
}

void	move_to_beginning(t_elem_cmd *tmp)
{
	t_elem_cmd *copy;

	copy = tmp;
	while (tmp->prev != NULL && tmp->prev->token != SEMICOLON &&
	tmp->prev->token != PIPE)
		tmp = tmp->prev;
	if (tmp->token == CMD)
	{
		tmp = tmp->next;
		while (tmp->token == ARG)
			tmp = tmp->next;
		delete_arg(copy, copy->next, copy->prev);
		insert_after_cmd(copy, tmp->prev, tmp);
		return ;
	}
	else
	{
		delete_arg(copy, copy->next, copy->prev);
		insert_after_null(copy);
	}
}

void	change_token(void)
{
	t_elem_cmd	*tmp;
	int			prev_token;

	tmp = g_all.first_cmd;
	prev_token = 0;
	while (tmp != NULL)
	{
		if (tmp->token != CMD && tmp->token != ARG)
			prev_token = tmp->token;
		if ((prev_token == RIGHT || prev_token == LEFT ||
		prev_token == DOUBLERIGHT)
		&& tmp->token == ARG && tmp->prev != NULL && tmp->prev->token == ARG)
			move_to_beginning(tmp);
		tmp = tmp->next;
	}
}
