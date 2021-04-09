/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 15:41:42 by macbookpro        #+#    #+#             */
/*   Updated: 2021/04/07 15:41:43 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** but de la fonction : trouver le bon token
** action de la fonction : trouve le bon token pour str
** str : le mot qui va obtenir un token
** tmp : element tampon de la liste chaine cmd
*/

void	search_token(char *str, t_elem_cmd *tmp, t_elem_cmd *prev)
{
	if (ft_strcmp(str, "|") == 0)
		tmp->token = PIPE;
	else if (ft_strcmp(str, ">>") == 0)
		tmp->token = DOUBLERIGHT;
	else if (ft_strcmp(str, ">") == 0)
		tmp->token = RIGHT;
	else if (ft_strcmp(str, "<") == 0)
		tmp->token = LEFT;
	else if (ft_strcmp(str, ";") == 0)
		tmp->token = SEMICOLON;
	else if (prev == NULL || prev->token == SEMICOLON || prev->token == PIPE)
		tmp->token = CMD;
	else
		tmp->token = ARG;
}

/*
** but de la fct: attribuer un token a chaque mot
** action : parcourt la liste chainés et appelle search token
*/

void	give_list_token(void)
{
	t_elem_cmd *tmp;
	t_elem_cmd *prev;

	prev = NULL;
	tmp = g_all.first_cmd;
	while (tmp && tmp->next)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	search_token(tmp->cmd, tmp, prev);
}
