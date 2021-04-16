/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2021/04/16 17:29:38 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_term(void)
{
	struct termios term;

	tgetent(NULL, getenv("TERM"));
	setupterm(NULL, STDOUT_FILENO, NULL);
	tcgetattr(0, &term);
	term.c_lflag &= ~(ICANON);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, 0, &term);
	g_all.term_x = tgetnum("co");
}

char	*free_last(void)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	str[0] = g_all.a;
	str[1] = '\0';
	g_all.a = 0;
	return (str);
}

void	minishell_parsing(void)
{
	write(1, COLORSTART, ft_strlen(COLORSTART));
	if (((verif_quote(g_all.buff) == 0)) &&
		(verif_end_backslash(g_all.buff) == 0))
		start_parsing();
	else if ((verif_quote(g_all.buff) == -1))
		ft_putstr_fd("Error : quote not closed\n", 2);
	else if ((verif_end_backslash(g_all.buff) == -1))
		ft_putstr_fd("Error : multiligne with '\\' \n", 2);
	write(1, NEWLINE, ft_strlen(NEWLINE));
	free_list_cmd();
}

int		main(int ac, char **av, char **envp)
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
		if (g_all.ctrl_c == 0)
			minishell_parsing();
		free(g_all.buff);
		g_all.ctrl_c = 0;
	}
	return (0);
}
