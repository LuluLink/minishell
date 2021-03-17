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

g_struct_all all;

struct struct_all
{
    elem_env *first_env;
    elem_cmd *first_cmd;
};


struct elem_cmd
{
    char *cmd;
    int  token;
    elem_cmd *next;
    elem_cmd *prev;
};

struct elem_env
{
    char *env;
    elem_env *next;
    elem_env *prev;
};

int        get_next_line(char **line);
void    initialisation_strcut(all *all);

#endif