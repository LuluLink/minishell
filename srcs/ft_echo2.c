/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2021/04/17 16:13:54 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void		print_space(t_elem_cmd *actual)
{
	if (actual->next != NULL && actual->next->token == ARG &&
		actual->cmd[0] != '\0' && actual->next->cmd[0] != '\0' &&
		actual->cmd[ft_strlen(actual->cmd) - 1] != ' ')
		ft_putchar(' ');
}
