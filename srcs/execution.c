/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2021/03/28 11:03:38 by pacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_start_execution(t_elem_cmd *actual)
{
	ft_execution(actual);
	while (actual && actual->next)
	{
		actual = actual->next;
		if (actual && actual->next && actual->token == SEMICOLON)
		{
			actual = actual->next;
			ft_execution(actual);
		}
	}
}

void	ft_execution(t_elem_cmd *actual)
{
	if (!actual)
		return ;
	if (actual->prev && actual->prev->token == DOUBLERIGHT)
		printf("double right\n");// ft_doubleright(actual);
	if (actual->prev && actual->prev->token == RIGHT)
		printf("right\n");//ft_right(actual);
	if (actual->prev && actual->prev->token == LEFT)
		printf("left\n");// ft_left(actual);
	if (actual->prev && actual->prev->token == PIPE)
		printf("pipe\n");// ft_pipe(actual);
	if (actual->next != NULL && actual->next->token != SEMICOLON)
		ft_execution(actual->next);
	if (actual->token == CMD)
		launch_cmd(actual);
}
