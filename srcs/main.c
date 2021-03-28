/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2021/03/28 11:03:38 by pacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;
	initialisation_struct();
	init_liste_env(envp);
	write(1, NEWLINE, ft_strlen(NEWLINE));
	while (get_next_line(&g_all.buff) > 0)
	{
		write(1, COLORSTART, ft_strlen(COLORSTART));
		if (((verif_quote(g_all.buff) == 0)) &&
		(verif_end_backslash(g_all.buff) == 0))
			start_parsing(g_all.buff);
		else if ((verif_quote(g_all.buff) == -1))
			ft_putstr_fd("Error : quote not closed\n", 2);
		else if ((verif_end_backslash(g_all.buff) == -1))
			ft_putstr_fd("Error : multiligne with '\\' \n", 2);
		write(1, NEWLINE, ft_strlen(NEWLINE));
		free_list_cmd();
		free(g_all.buff);
	}
	free_list_cmd();
	free_list_env();
	free(g_all.buff);
	return (0);
}
