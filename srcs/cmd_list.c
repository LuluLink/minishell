/*#include "minishell.h"


void    insertion_end_cmd(char *str)
{
    t_elem_cmd *nouveau = malloc(sizeof(*nouveau));
    t_elem_cmd *tmp = g_all.first_cmd;
    nouveau->cmd = str;
    if (tmp->next == NULL)
    {
        tmp->next = nouveau;
        nouveau->next = NULL;
        nouveau->prev = g_all.first_cmd;
    }
    while(tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    tmp->next = nouveau;
    nouveau->next = NULL;
    nouveau->prev = tmp->prev->next;
}

void    initialisation_cmd(char *str)
{
    g_all.first_cmd = malloc(sizeof(char*));
    t_elem_cmd *cmd = malloc(sizeof(*cmd));

    cmd->cmd = str;
    cmd->next = NULL;
    cmd->prev = NULL;
    g_all.first_cmd = cmd;
}

void    cmd_list(char *line)
{
    int     i;
    int     init;
    char    *str;

    i = 0;
    init = 0;
    while (line[i] != '\0')
    {
        if ((ft_isspace(line[i]) == 1))
        {
            if (init == 0)
            {
                str = line_cut(line);
                initialisation_cmd(str);
                init = 1;
            }
            else
            {
                insertion_end_cmd(str);
            }
        }
    }
}*/