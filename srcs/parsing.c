#include "minishell.h"

/*

** check_token check si le char envoyé est un tocken " ' | < > $
** si i vaut 0 il check tous les tokens
** si i vaut 1 il ne check que les separateurs

*/

int     check_backslash(char *str, int i)
{
    int ischar;
    ischar = 1;
    while (--i >= 0 && str[i] == '\\')
    {
        if (ischar == 0)
            ischar = 1;
        else
            ischar = 0;
    }
    return (ischar);
}

int     check_token(char *str, int k, int i)
{
    int j;

    j = 0;
    if (i == 0)
        if (str[k] == '<' || str[k] == '>' || str[k] == '|' || str[k] == '\'' || str[k] == '\"' || str[k] == '$' || str[k] == ';')
            j = check_backslash(str, k);
    if (i == 1)
        if (str[k] == '<' || str[k] == '>' || str[k] == '|' || str[k] == ';')
            j = check_backslash(str, k);
    return (j);
}

int     ft_skipspaces(char *str)
{
    int i;

    i = 0;
    while (str[i] && ft_isspace(str[i]))
        i++;
    return (i);
}

int     pass_quote(char *str, int j)
{
    int i;
    char a;

    i = 0;
    if (str[i] && j == 1 && (str[i] == '\'' || str[i] == '\"'))
    {
        a = str[i];
        i++;
        while (str[i])
        {
            if (str[i] == a)
                if (check_backslash(str, i))
                    break ;
            i++;
        }
        return (i + 1);
    }
    else 
        return (1);
}

int    check_last()
{
    t_elem_cmd *tmp;

    tmp = g_all.first_cmd;
    while (tmp && tmp->next)
        tmp = tmp->next;
    if (tmp)
    {
        if (tmp->token == ARG)
        {
            printf("Syntax error : '%s'\n", tmp->cmd);
            free_list_cmd();
            return (1);
        }
    }
    return (0);
}

int     check_dollar(char *str, t_elem_cmd  *tmp)
{
    int i;
    int j;
    int quote;
    char *str2;

    i = 0;
    quote = 0;
    str2 = ft_strdup("");
    while (str[i])
    {
        j = 0;
        while (str[i + j] && (str[i + j] != '$' || quote == 1))
        {
            if (str[i + j] == '\'' && check_backslash(str, i + j) && quote != 2)
                    quote = (quote == 0) ? 1 : 0;
            if (str[i + j] == '\"' && check_backslash(str, i + j) && quote != 1)
                    quote = (quote == 0) ? 2 : 0;
            j++;
        }
        str2 = ft_strjoin(str2, ft_strndup(&str[i], j));
        i += j;
        j = 1;
        if (str[i] == '$' && quote != 1 && check_backslash(str, i))
        {
            while (str[i + j] && (ft_isalnum(str[i + j]) || str[i + j] == '_'))
                j++;
            str2 = ft_strjoin(str2, chrenv(ft_strndup(&str[i + 1], j - 1)));
            i += j;
        }
    }
    free(tmp->cmd);
    tmp->cmd = str2;
    return 0;
}

void    check_env()
{
    t_elem_cmd  *tmp;

    tmp = g_all.first_cmd;
    while (tmp)
    {
        if (tmp->token == ARG || tmp->token == CMD)
        {
            check_dollar(tmp->cmd, tmp);
        }
        tmp = tmp->next;
    }
}

void    start_parsing(char *buff)
{
    int i;
    int j;
	int pid;

    i = 0;
	pid = 0;
    while (buff[i])
    {
        j = 0;
        while (buff[i + j] && !check_token(buff, i + j, 1) && !ft_isspace(buff[i + j]))
            j += pass_quote(&buff[i + j], check_backslash(buff, i + j));
        if (j > 0)
            insertion_end_cmd(ft_strndup(&buff[i], j), 0); //ICI C EST DU TEXT
        i += j + ft_skipspaces(&buff[i + j]);    
        j = 0;
        while (buff[i + j] && check_token(buff, i + j, 1) && !ft_isspace(buff[i + j]))
            j++;
        if (j > 0)
        {
            insertion_end_cmd(ft_strndup(&buff[i], j), 0); //ICI C EST UN TOKEN     
            if (check_last())
                return ;
        }
        i += j + ft_skipspaces(&buff[i + j]);
    }
    check_env();
    ft_start_execution(g_all.first_cmd, pid);
}