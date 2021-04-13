/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 13:24:11 by macbookpro        #+#    #+#             */
/*   Updated: 2021/04/13 13:25:18 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_quote_for_dollar(int *quote, char *str, int *j, int *i)
{
	if (str[i[0] + j[0]] == '\'' && check_backslash(str, i[0]
	+ j[0]) && quote[0] != 2)
		quote[0] = (quote[0] == 0) ? 1 : 0;
	if (str[i[0] + j[0]] == '\"' && check_backslash(str, i[0]
	+ j[0]) && quote[0] != 1)
		quote[0] = (quote[0] == 0) ? 2 : 0;
	j[0] = (str[i[0] + j[0] + 1] == '$' && quote[0] != 1 &&
	!check_backslash(str, i[0] + j[0] + 1)) ? j[0] + 2 : j[0] + 1;
}
