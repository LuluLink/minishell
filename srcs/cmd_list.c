/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2021/04/07 15:41:01 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_liste_cmd(void)
{
	t_elem_cmd *actuel;

	actuel = g_all.first_cmd;
	while (actuel != NULL)
	{
		printf("token :%d, liste :%s\n", actuel->token, actuel->cmd);
		actuel = actuel->next;
	}
}

void	initialisation_cmd(char *str, int token)
{
	t_elem_cmd *cmd;

	cmd = malloc(sizeof(t_elem_cmd));
	cmd->cmd = str;
	cmd->token = token;
	cmd->next = NULL;
	cmd->prev = NULL;
	g_all.first_cmd = cmd;
}

void	ft_add_back(t_elem_cmd *tmp, t_elem_cmd *nouveau)
{
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = nouveau;
	nouveau->next = NULL;
	nouveau->prev = tmp;
}

void	insertion_end_cmd(char *str, int token)
{
	t_elem_cmd *nouveau;
	t_elem_cmd *tmp;

	nouveau = malloc(sizeof(t_elem_cmd));
	tmp = g_all.first_cmd;
	if (tmp == NULL)
	{
		free(nouveau);
		initialisation_cmd(str, token);
		give_list_token();
		return ;
	}
	nouveau->cmd = str;
	nouveau->token = token;
	if (tmp->next == NULL)
	{
		tmp->next = nouveau;
		nouveau->next = NULL;
		nouveau->prev = g_all.first_cmd;
		give_list_token();
		return ;
	}
	ft_add_back(tmp, nouveau);
	give_list_token();
}

void	free_list_cmd(void)
{
	t_elem_cmd *tmp;

	tmp = g_all.first_cmd;
	while (tmp != NULL)
	{
		free(tmp->cmd);
		g_all.first_cmd = g_all.first_cmd->next;
		free(tmp);
		tmp = g_all.first_cmd;
	}
}
