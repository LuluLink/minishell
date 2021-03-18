#include "minishell.h"


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

char    *line_cut(char  *line, int i)
{
    char    *dest;
    int     j;

    j = 0;
    while ((ft_isspace(line[i]) == 0))
    {
        if (line[i] == '\"' || line[i] == '\'')
        {
            i--;
            j++;
            while (line[i] != '\"' || line[i] != '\'')
            {
                i--;
                j++;
            }
        }
        i--;
        j++;
    }
    dest = malloc(sizeof(char) * (j + 1));
    dest[j] = '\0';
    i = i + 1;
    j = 0;
    while (dest[j] != '\0')
    {
        dest[j] = line[i];
        j++;
        i++;
    }
    return (dest);
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
        if (line[i] == '\"' || line[i] == '\'')
        {
            i++;
            while (line[i] != '\"' || line[i] != '\'')
                i++;
        }
        if ((ft_isspace(line[i]) == 1))
        {
            if (init == 1)
            {
                str = line_cut(line, i- 1);
                insertion_end_cmd(str, g_all);
            }
            if (init == 0)
            {
                str = line_cut(line, i - 1);
                initialisation_cmd(str, g_all);
                init = 1;
            }
        }
    }
    give_list_token();
}