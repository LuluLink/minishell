/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 14:52:39 by macbookpro        #+#    #+#             */
/*   Updated: 2021/04/24 14:59:34 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	enable_canon(void)
{
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag |= (ICANON);
	tcsetattr(0, 0, &term);
}

void	disable_canon(void)
{
	struct termios	term;

	tcgetattr(0, &term);
	if (ENABLE_CANON == 1)
		term.c_lflag &= ~(ICANON);
	else
		term.c_lflag = ~(ICANON);
	tcsetattr(0, 0, &term);
}
