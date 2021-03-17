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
# include "libft.h"

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
    t_elem_env *first_env;
    t_elem_cmd *first_cmd;
}   t_struct_all;

t_struct_all g_all;

int         ft_isspace(int c);
int         get_next_line(char **line);
void        initialisation_struct(t_struct_all *all);
void        ft_putstr(char *str);
void        initialisation_env(char *str, t_struct_all *g_all);
void        print_liste_env(t_struct_all *g_all);
void        init_liste_env(char **envp, t_struct_all *g_all);
int         ft_strcmp(char *s1, char *s2);

#endif