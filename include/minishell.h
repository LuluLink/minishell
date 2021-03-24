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

# define RIGHT 1
# define DOUBLERIGHT 2
# define LEFT 3
# define PIPE 4
# define ARG 5
# define CMD 6
# define SEMICOLON 7

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

typedef struct s_struct_all
{
    int         quote;
    int         d_quote;
    char        *buff;
    t_elem_env *first_env;
    t_elem_cmd *first_cmd;
}   t_struct_all;

t_struct_all g_all;

int         ft_isspace(int c);
int         get_next_line(char **line);
void        initialisation_struct();
void        ft_putstr(char *str);
void        initialisation_env(char *str);
void        print_liste_env();
void        init_liste_env(char **envp);
int         ft_strcmp(char *s1, char *s2);
char        *chrenv(char *str);
void        start_parsing(char *buff);
char        *ft_strndup(const char *src, int n);
void        give_list_token();
void        ft_putchar(char c);
int         ft_strlen(const char *str);
int         ft_strncmp(char *s1, char *s2, unsigned int n);
char        *ft_strdup(const char *src);
char    	*ft_strjoin(char *s1, char *s2);
char    	*ft_strnjoin(char *s1, char *s2, int n);
char	    *ft_strjoinchar(char *s1, char s2);
void        cmd_list(char *line);
void        print_liste_cmd();
void        insertion_end_cmd(char *str, int token);
int         verif_quote(char *line);
void	    ft_putstr_fd(char *s, int fd);
int         verif_end_backslash(char *line);
void        free_list_cmd();
void        free_list_env();
int         ft_isalnum(int c);
void        ft_execution(t_elem_cmd *actual);
void        launch_cmd(t_elem_cmd *tmp);
char        **ft_split(char *str, char c);
void        ft_exit();
void        ft_env();
void        ft_unset(char *str);
void        suppression_middle_env(t_elem_env *liste);

#endif