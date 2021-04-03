/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2021/03/28 11:03:38 by pacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int		verif_nb_arg(t_elem_cmd *actual)
{
	t_elem_cmd *tmp;
	int i;

	i = 0;
	tmp = actual->next;
	while (tmp != NULL && tmp->token == ARG)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int		verif_first_arg(t_elem_cmd *actual)
{
	t_elem_cmd	*tmp;
	int			i;
	int nb;

	i = 0;
	nb = 0;
	tmp = actual->next;
	while (tmp->cmd[i] != '\0')
	{
		if ((tmp->cmd[i] >= '0' && tmp->cmd[i] <= '9') || tmp->cmd[i] == '-' || tmp->cmd[i] == '+')
		{
			if (tmp->cmd[i] == '-' || tmp->cmd[i] == '+')
				nb++;
			i++;
		}
		else
			return (-1);
	}
	if (nb > 1)
		return (-1);
	return (0);
}

void	quit_minishell(void)
{
	free_list_cmd();
	free_list_env();
	free(g_all.buff);
	printf("exit\n");
	exit(g_all.exit_code);
}

void	ft_exit(t_elem_cmd *actual)
{
	int i;
	int verif_arg;

	if (actual->next == NULL)
		quit_minishell();
	verif_arg = verif_first_arg(actual);
	i = verif_nb_arg(actual);
	if (i > 1 && verif_arg == 0)
	{
		printf("exit\n");
		ft_putstr_fd("trop d'argument", 2);
		return ;
	}
	if (verif_arg == -1)
	{
		printf("exit\n");
		ft_putstr_fd("argument numerique necessaire", 2);
		g_all.exit_code = 2;
		quit_minishell();
	}
	g_all.exit_code = ft_atoi(actual->next->cmd);
	while (g_all.exit_code < 0)
		g_all.exit_code = g_all.exit_code + 256;
	if (g_all.exit_code > 255)
		g_all.exit_code = g_all.exit_code % 256;
	quit_minishell();
}