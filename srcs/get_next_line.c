/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2021/04/07 14:02:11 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *recurs(int index, int *ret, int fd)
{
    char    buff[1];
    char    *str;
    int        test;
    test = read(fd, buff, 1); // on lit UN SEUL caractere
    check_arrow(&buff[0]);
    if (test == 0) // si le read ne lit rien
        buff[0] = 0;
    if (buff[0] == '\n' || buff[0] == 0) //si le caractere actuel est 0 ou \n
    {
        if (!(str = malloc(sizeof(char) * index + 1)))
            return (0);
        str[index] = 0;
        *ret = 1;
        if (buff[0] == 0)
            *ret = 0;
        return (str);
    }
    else
    {
        if (!(str = recurs(index + 1, ret, fd)))
            return (0);
        str[index] = buff[0];
    }
    return (str);
}

void        aff_lst_cmd(void)
{
    t_elem_env  *tmp;

    tmp = g_all.cmd_lst;
    while (tmp)
    {
        printf("tmp->env : %s\n", tmp->env);
        tmp= tmp->next;
    }
}

char        *keep_printable(char *str)
{
    char    *a;

    if (g_all.arrow == 1 || g_all.arrow == 2)
    {
        a = ft_strndup(str, ft_strlen(str) - 2);
        free(str);
    }
    else
        a = str;
    return (a);
}

void        ft_supp(char *str)
{
    int     i;

    i = 0;
    while (str[i])
        i++;
    if (i > 0)
        i -= 1;
    str[i] = '\0';
}

void        init_gnl(char **line)
{
    g_all.arrow = 1;
    g_all.cursor = 0;
    *line = NULL;
    insertion_end_lst("");
}

int        get_next_line(char **line)
{
    int     ret;
    
    ret = 1;
    init_gnl(line);
    while (g_all.arrow != 0)
    {
        g_all.arrow = 0;
        if (!*line)
            *line = keep_printable(recurs(0, &ret, 0));
        else
            *line = ft_strjoin(*line, keep_printable(recurs(0, &ret, 0)));
        if (g_all.str)
        {
            *line = ft_strjoin(g_all.str, *line);
            g_all.str = NULL;
        }
        if (g_all.arrow == 3)
            ft_supp(*line);
        if (g_all.arrow == 0 && ft_strlen(*line) > 0)
        {
            cmd_rm_last();
            insertion_end_lst(*line);
        }
        if (g_all.arrow == 1 || g_all.arrow == 2)
        {
            if (g_all.index == lst_len() - 1)
            {
                cmd_rm_last();
                insertion_end_lst(*line);
            }
            free(*line);
            *line = NULL;
            cmd_histo();
        }
        else if (g_all.arrow == 0)
            g_all.index = lst_len();
    }
    if (g_all.str)
        free(g_all.str);
    g_all.str = NULL;
    return (ret);
}