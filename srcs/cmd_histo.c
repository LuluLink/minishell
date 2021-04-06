#include "minishell.h"

void    cmd_add_back(t_elem_env *new)
{
	t_elem_env	*tmp;

	if (!new)
		return ;
    new->next = NULL;
	if (g_all.cmd_lst)
	{
		tmp = g_all.cmd_lst;
		while (tmp->next)
			tmp = tmp->next;
        new->prev = tmp;
		tmp->next = new;
	}
	else
		g_all.cmd_lst = new;
}

void	insertion_end_lst(char *str)
{
	t_elem_env *nouveau;

	nouveau = malloc(sizeof(t_elem_env));
    if (g_all.arrow == 1 && ft_strlen(str) > 2)
        nouveau->env = str;
    else
        nouveau->env = ft_strdup(str);
    cmd_add_back(nouveau);
    t_elem_env *tmp;
    tmp = g_all.cmd_lst;
    int i = 0;
    while (tmp != NULL)
    {
        //printf("maillon %2d: |%s|\n", i, tmp->env);
        i++;
        tmp = tmp->next;
    }
}

int     lst_len(void)
{
    t_elem_env  *tmp;
    int         i;

    tmp = g_all.cmd_lst;
    i = 0;
    while (tmp)
    {
        tmp = tmp->next;
        i++;
    }
    return (i);
}

int    ft_myputchar(int a)
{
    write(1, &a, 1);
    return (0);
}

void    ft_aff_index(void)
{
    char        *cl_cap;
    t_elem_env  *tmp;
    int         i;

    i = 0;
    tmp = g_all.cmd_lst;
    while (tmp && i++ < g_all.index)
        tmp = tmp->next;
    //printf("\nlen : %2d, line : |%s|\n", ft_strlen(tmp->env), tmp->env);
    cl_cap = tgetstr("dl", NULL); // dl cd
    tputs(cl_cap, 1, ft_myputchar);
    write(1, NEWLINE, ft_strlen(NEWLINE));
    //printf("cursor : %d\n", g_all.cursor);
    write(1, tmp->env, ft_strlen(tmp->env));
    //printf("cursor av : %d\n", g_all.cursor);
    g_all.cursor = ft_strlen(tmp->env);
    if (g_all.str)
        free(g_all.str);
    g_all.str = ft_strdup(tmp->env);
    //printf("cursor ap : %d\n", g_all.cursor);
}

void    cmd_histo(void)
{
    if (g_all.arrow == 1)
    {
        g_all.index = (g_all.index > 0) ? g_all.index - 1 : g_all.index;
        ft_aff_index();
    }
    else if (g_all.arrow == 2)
    {
        g_all.index = (g_all.index < lst_len() - 1) ? g_all.index + 1 : lst_len() - 1;
        ft_aff_index();
    }
}


/*
** g_all.arrow 1 -> fleche du haut
**             2 -> fleche du bas
*/


void    check_arrow(char *a)
{
	static int i;
    if (a[0] == 127)
    {
        if (g_all.cursor > 0)
            tputs(tgetstr("le", NULL), 1, ft_myputchar);
        g_all.cursor = (g_all.cursor > 0) ? g_all.cursor - 1 : g_all.cursor;
        tputs(tgetstr("le", NULL), 1, ft_myputchar);
        tputs(tgetstr("le", NULL), 1, ft_myputchar);
        tputs(tgetstr("ce", NULL), 1, ft_myputchar);
        a[0] = '\n';
        g_all.arrow = 3;  
    }
    else if (i == 0 && a[0] == 27)
        i = 1;
    else if (i == 1 && a[0] == '[')
        i = 2;
    else if (i == 2 && a[0] == 'A')
    {
        a[0] = '\n';
        g_all.arrow = 1;  
        i = 0; 
    }
    else if (i == 2 && a[0] == 'B')
    {
        a[0] = '\n';
        g_all.arrow = 2;
        i = 0;
    }
    else
    {
        i = 0;
        g_all.cursor++;
        //printf("cursor : %d\n", g_all.cursor);
    }
}