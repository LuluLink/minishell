/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2021/04/06 11:36:14 by macbookpro       ###   ########.fr       */
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
    int     i;
    int     j;
    int     k;

    i = 0;
    j = -1;
    //printf("str : %s\n", str);
    while (str[++j])
        if (str[j] >= 32 && str[j] < 127)
            i++;
    if (!(a = malloc(sizeof(char) * (i + 1))))
        return (NULL);
    j = 0;
    k = 0;
    while (j < i)
    {
        while (str[k] >= 127 || str[k] < 32)
            k++;
        a[j++] = str[k++];
    }
    a[j] = '\0';
    free(str);
    //printf("a   : %s\n", a);
    return (a);
}
void        ft_supp(char *str)
{
    int     i;
    //int     len;
    
    //printf("\nlen : %d, str : |%s|\n", ft_strlen(str), str);
   // len = ft_strlen(str);
    i = 0;
    while (str[i])
        i++;
    if (i > 0)
        i -= 1;
    str[i] = '\0';
    //printf("len : %d, str : |%s|\n", ft_strlen(str), str);
}

int        get_next_line(char **line)
{
    int     ret;
    char    *tmp;
    
    ret = 1;
    g_all.arrow = 1;
    g_all.cursor = 0;
    *line = NULL;
    while (g_all.arrow != 0)
    {
        g_all.arrow = 0;
        if (!*line)
            *line = recurs(0, &ret, 0);
        else
            *line = ft_strjoin(*line, recurs(0, &ret, 0));
        if (g_all.str)
        {
            //*line = ft_strjoin(g_all.str, *line);
            free(*line);
            *line = g_all.str;
            g_all.str = NULL;
        }
        if (g_all.arrow == 3)
            ft_supp(*line);
        if (g_all.arrow == 0 && ft_strlen(*line) > 0)
        {
            tmp = keep_printable(ft_strdup(*line));
            insertion_end_lst(tmp);
            free(tmp);
        }
        else if (g_all.arrow == 1 && ft_strlen(*line) > 2)
        {
            tmp = *line;
            *line = keep_printable(ft_strndup(*line, ft_strlen(*line) - 2));
            free(tmp);
            insertion_end_lst(*line);
        }
        if (g_all.arrow != 0 && g_all.arrow != 3)
            cmd_histo();
        else if (g_all.arrow != 3)
            g_all.index = lst_len();
        //printf("\nindex : %d\n", g_all.index);
    }
    if (g_all.str)
        free(g_all.str);
    g_all.str = NULL;
    //aff_lst_cmd();
    //printf("line : |%s|\n", *line);
    return (ret);
}