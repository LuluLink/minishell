#include "minishell.h"

void print_liste_cmd()
{
    t_elem_cmd *actuel = g_all.first_cmd;

    while (actuel != NULL)
    {
        printf("token :%d, liste :%s\n", actuel->token, actuel->cmd);
        actuel = actuel->next;
    }
}

//initialise la liste cmd en lui passant le premier mot

void    initialisation_cmd(char *str, int token)
{
    //g_all.first_cmd = malloc(sizeof(char*));
    t_elem_cmd *cmd = malloc(sizeof(t_elem_cmd));

    cmd->cmd = str;
    cmd->token = token;
    cmd->next = NULL;
    cmd->prev = NULL;
    g_all.first_cmd = cmd;
}

void    insertion_end_cmd(char *str, int token)
{
    t_elem_cmd *nouveau = malloc(sizeof(t_elem_cmd));
    t_elem_cmd *tmp = g_all.first_cmd;
    if (tmp == NULL)
    {
        free(nouveau);
        initialisation_cmd(str, token);
        give_list_token();
        return ;
    }
    nouveau->cmd = str;
    nouveau->token = token;
    if (tmp->next == NULL)
    {
        tmp->next = nouveau;
        nouveau->next = NULL;
        nouveau->prev = g_all.first_cmd;
        give_list_token();
        return ;
    }
    while(tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = nouveau;
    nouveau->next = NULL;
    nouveau->prev = tmp;
    give_list_token();
}

/*
 but de la fct : découper les mots de la ligne de commande
 action de la fct : créer un char * qui va contenir le mot sans espace
 line = ligne de commandes
 i = position dans la ligne de commande.

*/

char    *line_cut(char  *line, int i)
{
    char    *dest;
    int     j;

    j = 0;
    while ((ft_isspace(line[i]) == 0) && line[i] != '\0' && i > 0)
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
    if (i == 0 && (ft_isspace(line[i]) == 0))
        j++;
    dest = malloc(sizeof(char) * (j + 1));
    dest[j] = '\0';
    if (i != 0)
        i = i + 1;
    j = 0;
    while (dest[j] != '\0' && line[i] != '\0')
    {
        dest[j] = line[i];
        j++;
        i++;
    }
    return (dest);
}

void    free_list_cmd()
{
    t_elem_cmd *tmp;
    tmp = g_all.first_cmd;
    while (tmp != NULL)
    {
        free(tmp->cmd);
        g_all.first_cmd = g_all.first_cmd->next;
        free(tmp);
        tmp = g_all.first_cmd;
    }
    //free(g_all.first_cmd);
}

/*
 but de la fct: mettre la ligne de commandes dans une liste chaines et attribuer des tokens

 action de la fct : parcourt line et s'arrete au premier espace/whitespace

 line : pointeur sur la ligne de commande entré par l'utilisateurs

 return : void

*/

/*void    cmd_list(char *line)
{
    int     i;
    int     init;
    //char    *str;

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
                str = line_cut(line, i - 1);
               // insertion_end_cmd(str);
            }
            if (init == 0)
            {
                str = line_cut(line, i - 1);
               // initialisation_cmd(str);
                init = 1;
            }
        }
        i++;
    }
    give_list_token();
}*/