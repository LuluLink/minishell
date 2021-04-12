/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 15:41:39 by macbookpro        #+#    #+#             */
/*   Updated: 2021/04/07 15:41:40 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	initialisation_struct(void)
{
	g_all.first_cmd = NULL;
	g_all.first_env = NULL;
	g_all.cmd_lst = NULL;
	g_all.str = NULL;
	g_all.exit = 0;
	g_all.fdout = -1;
	g_all.fdin = -1;
	g_all.standardin = dup(0);
	g_all.standardout = dup(1);
	g_all.child = 0;
	g_all.pipefdin = -1;
	g_all.pipefdout = -1;
	g_all.block_cmd = 0;
	g_all.exit_code = 0;
	g_all.arrow = 0;
	g_all.index = 0;
	g_all.cursor = 0;
	g_all.ctrl_c = 0;
	g_all.in_loop = 0;
	ft_aff_minishell();
}
