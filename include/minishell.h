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

typedef struct s_elem_cmd
{
    char *cmd;
    int  token;
    struct  s_elem_cmd *next;
    struct  s_elem_cmd *prev;
}       t_elem_cmd;


typedef struct s_elem_env
{
    char *env;
    struct  s_elem_env *next;
    struct  s_elem_env *prev;
}      t_elem_env;

typedef struct  s_struct_all
{
    int         arrow;
    int 		block_cmd;
    char        *buff;
    int			child;
    int         cursor;
    int			d_quote;
    int			exit;
    int			exit_code;
    int			fdin;
    int			fdout;
    int			index;
    int			pipefdin;
	int			pipefdout;
	int			dad;
	int			ctrl_c;
    int			quote;
    int			standardin;
	int			standardout;
    char        *str;
	int			i;
	int			j;
    t_elem_env  *cmd_lst;
    t_elem_env  *first_env;
    t_elem_cmd  *first_cmd;
}               t_struct_all;

t_struct_all g_all;

int			ft_isspace(int c);
int			get_next_line(char **line);
void		initialisation_struct();
void		ft_putstr(char *str);
void		initialisation_env(char *str);
void		print_liste_env();
void		init_liste_env(char **envp);
int		 	ft_strcmp(char *s1, char *s2);
char		*chrenv(char *str);
void		start_parsing(char *buff);
char		*ft_strndup(const char *src, int n);
void		give_list_token();
void		ft_putchar(char c);
int			ft_strlen(const char *str);
int			ft_strncmp(char *s1, char *s2, unsigned int n);
char		*ft_strdup(const char *src);
char    	*ft_strjoin(char *s1, char *s2);
char    	*ft_strnjoin(char *s1, char *s2, int n);
char	    *ft_strjoinchar(char *s1, char s2);
void		cmd_list(char *line);
void		print_liste_cmd();
void		insertion_end_cmd(char *str, int token);
int			verif_quote(char *line);
void	    ft_putstr_fd(char *s, int fd);
int			verif_end_backslash(char *line);
void		free_list_cmd();
void		free_list_env();
int			ft_isalnum(int c);
void		ft_execution(t_elem_cmd *actual);
void		launch_cmd(t_elem_cmd *tmp);
char		**ft_split(char *str, char c);
void		ft_exit(t_elem_cmd *actual);
int			ft_env(t_elem_cmd *actual);
int			ft_unset(t_elem_cmd *actual);
void		suppression_middle_env(t_elem_env *liste);
void		free_double_char(char **str);
int			ft_export(t_elem_cmd *actual);
void		insertion_end_env(char *str);
void		ft_putstr_fd(char *s, int fd);
char		**liste_env_to_wordtab();
void		ft_start_execution(t_elem_cmd *actual, int pid);
int			ft_pwd(void);
int			ft_echo(t_elem_cmd *actual);
void		free_list_env_sort(t_elem_env *lst);
void		ft_aff_minishell(void);
int			ft_cd(char *path);
void		ft_right(t_elem_cmd *actual);
void        check_arrow(char *a);
void        insertion_end_lst(char *str);
void        cmd_histo(void);
int         lst_len(void);
void		ft_doubleright(t_elem_cmd *actual);
void		ft_left(t_elem_cmd *actual);
int			ft_pipe();
int			ft_atoi(char *str);
void        cmd_rm_last(void);
void		ft_signal_hander_c(int signal);
void		quit_minishell(void);
void		ft_signal_hander_backslash(int signal);
char		*str_to_env(char *str);
int			print_env(t_elem_env *tmp, int i, int verif_quote);
int			remplace_env(char *str);
char		*check_cmd(t_elem_cmd *tmp);

#endif