/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 18:05:30 by macbookpro        #+#    #+#             */
/*   Updated: 2021/04/19 17:36:22 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <signal.h>

# define RIGHT 1
# define DOUBLERIGHT 2
# define LEFT 3
# define PIPE 4
# define ARG 5
# define CMD 6
# define SEMICOLON 7
# define NEWLINE "\e[1m\e[38;5;82m$> \e[0m"
# define COLORSTART "\e[38;5;226m"
# define COLOREND "\e[0m"
# define STRERRORCOLOR "\e[38;5;196m"

typedef struct			s_elem_cmd
{
	char				*cmd;
	int					token;
	struct s_elem_cmd	*next;
	struct s_elem_cmd	*prev;
}						t_elem_cmd;

typedef struct			s_elem_env
{
	char				*env;
	struct s_elem_env	*next;
	struct s_elem_env	*prev;
}						t_elem_env;

typedef struct			s_struct_all
{
	int					arrow;
	int					block_cmd;
	char				*buff;
	int					child;
	int					cursor;
	int					d_quote;
	int					exit;
	int					exit_code;
	int					fdin;
	int					fdout;
	int					index;
	int					pipefdin;
	int					pipefdout;
	int					dad;
	int					ctrl_c;
	int					ctrl_d;
	int					quote;
	int					standardin;
	int					standardout;
	char				*str;
	int					i;
	int					j;
	char				a;
	int					in_loop;
	int					term_x;
	int					cursor_x;
	int					sep;
	int					error;
	char				*err_tmp;
	t_elem_env			*cmd_lst;
	t_elem_env			*first_env;
	t_elem_cmd			*first_cmd;
	t_elem_cmd			*wildcard;
}						t_struct_all;

t_struct_all			g_all;

int						ft_isspace(int c);
int						get_next_line(char **line);
void					initialisation_struct();
void					ft_putstr(char *str);
void					initialisation_env(char *str);
void					print_liste_env();
void					init_liste_env(char **envp);
int						ft_strcmp(char *s1, char *s2);
char					*chrenv(char *str);
void					start_parsing(void);
char					*ft_strndup(const char *src, int n);
void					give_list_token();
void					ft_putchar(char c);
int						ft_strlen(const char *str);
int						ft_strncmp(char *s1, char *s2, unsigned int n);
char					*ft_strdup(const char *src);
char					*ft_strjoin(char *s1, char *s2);
char					*ft_strnjoin(char *s1, char *s2, int n);
char					*ft_strjoinchar(char *s1, char s2);
void					cmd_list(char *line);
void					print_liste_cmd();
void					insertion_end_cmd(char *str, int token);
int						verif_quote(char *line);
void					ft_putstr_fd(char *s, int fd);
int						verif_end_backslash(char *line);
void					free_list_cmd();
void					free_list_env();
int						ft_isalnum(int c);
void					ft_execution(t_elem_cmd *actual);
void					launch_cmd(t_elem_cmd *tmp);
char					**ft_split(char *str, char c);
void					ft_exit(t_elem_cmd *actual);
int						ft_env(t_elem_cmd *actual);
int						ft_unset(t_elem_cmd *actual);
void					suppression_middle_env(t_elem_env *liste);
void					free_double_char(char **str);
int						ft_export(t_elem_cmd *actual);
void					insertion_end_env(char *str);
void					ft_putstr_fd(char *s, int fd);
char					**liste_env_to_wordtab();
void					ft_start_execution(t_elem_cmd *actual, int pid);
int						ft_pwd(void);
int						ft_echo(t_elem_cmd *actual);
void					free_list_env_sort(t_elem_env *lst);
void					ft_aff_minishell(void);
int						ft_cd(char *path);
void					ft_right(t_elem_cmd *actual);
void					check_arrow(char *a);
void					insertion_end_lst(char *str);
void					cmd_histo(void);
int						lst_len(void);
void					ft_doubleright(t_elem_cmd *actual);
void					ft_left(t_elem_cmd *actual);
int						ft_pipe();
int						ft_atoi(char *str);
void					cmd_rm_last(void);
void					ft_signal_hander_c(int signal);
void					quit_minishell(void);
void					ft_signal_hander_backslash(int signal);
char					*str_to_env(char *str);
int						print_env(t_elem_env *tmp, int i, int verif_quote);
int						remplace_env(char *str);
char					*check_cmd(t_elem_cmd *tmp);
char					*free_last(void);
void					aff_lst_cmd(void);
char					*keep_printable(char *str);
void					ft_supp(char *str, int j);
void					if_arrow(char **line);
int						check_last(void);
char					*check_dollar(char *str);
void					check_env(void);
int						check_backslash(char *str, int i);
char					*ft_itoa(int n);
int						ft_mypc(int a);
void					ft_bs_alone(void);
void					ft_quote_for_dollar(int *quote,
char *str, int *j, int *i);
void					reset_var(void);
void					check_multiple_words(t_elem_cmd *tmp);
void					search_token(char *str, t_elem_cmd *tmp,
t_elem_cmd *prev);
int						ft_check_sep(void);
void					inc_i_j(void);
void					check_arrow2(int i, char *a);
void					rm_del2(void);
void					ctrl_d(char *a);
int						ft_cd2(char *str, char *error, int tofree, char *path);
void					print_error_export(char *str);
void					modif_pwd(char *path);
int						check_old(void);
void					cd_free(int tofree, char *path, char *str);
void					is_wildcard(char *path);
void					insertion_end_wild(char *str);
int						is_asterix(char *str);
void					ft_add_back(t_elem_cmd *tmp, t_elem_cmd *nouveau);
void					aff_dir(char **mytab, char *str, char *name, int index);
void					check_wild(void);
void					initialisation_wild(char *str, int token);
void					last_wc(t_elem_cmd *next);
void					ft_list_sort(t_elem_cmd **begin_list, int (*cmp)());
char					**ft_split_slash(char **str);
void					change_token(void);
void					print_space(t_elem_cmd *actual);

#endif
