#ifndef MINISHELL_H
# define MINISHELL_H
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>

typedef struct elem_cmd elem_cmd;
struct elem_cmd
{
    char *cmd;
    int  token;
    elem_cmd *next;
    elem_cmd *prev;
};
typedef struct elem_env elem_env;
struct elem_env
{
    char *env;
    elem_env *next;
    elem_env *prev;
};
typedef struct struct_all struct_all;
struct struct_all
{
    elem_env *first_env;
    elem_cmd *first_cmd;
};

struct_all g_all;

int        get_next_line(char **line);
void    initialisation_struct(struct_all *all);
void	ft_putstr(char *str);

#endif