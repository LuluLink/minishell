/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 15:34:23 by macbookpro        #+#    #+#             */
/*   Updated: 2021/04/13 15:35:27 by macbookpro       ###   ########.fr       */
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
