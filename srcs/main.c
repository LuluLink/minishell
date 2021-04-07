/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2021/04/05 13:24:02 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void                  init_term()
{
  struct termios   term;

	tgetent (NULL, getenv("TERM"));
	setupterm(NULL, STDOUT_FILENO, NULL);
	tcgetattr(0, &term);
  	//term.c_lflag &= ~(ECHO | ICANON);
  	term.c_lflag &= ~(ICANON);
  	term.c_cc[VMIN] = 1;
  	term.c_cc[VTIME] = 0;
  	tcsetattr(0, 0, &term);
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	initialisation_struct();
	init_term();
	init_liste_env(envp);
	write(1, NEWLINE, ft_strlen(NEWLINE));
	signal(SIGINT, ft_signal_hander_c);
	signal(SIGQUIT, ft_signal_hander_backslash);
	while (get_next_line(&g_all.buff) > 0)
	{
		signal(SIGINT, ft_signal_hander_c);
		signal(SIGQUIT, ft_signal_hander_backslash);
		if (g_all.arrow == 0)
		{
			write(1, COLORSTART, ft_strlen(COLORSTART));
			if (((verif_quote(g_all.buff) == 0)) &&
			(verif_end_backslash(g_all.buff) == 0))
				start_parsing(g_all.buff);
			else if ((verif_quote(g_all.buff) == -1))
				ft_putstr_fd("Error : quote not closed\n", 2);
			else if ((verif_end_backslash(g_all.buff) == -1))
				ft_putstr_fd("Error : multiligne with '\\' \n", 2);
			if (g_all.prompt == 0)
				write(1, NEWLINE, ft_strlen(NEWLINE));
			g_all.prompt = 0;
			free_list_cmd();
		}
		g_all.ctrl_c = 0;
		free(g_all.buff);
	}
	return (0);
}
