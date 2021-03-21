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

int     pass_quote(char *str)
{
    int i;
    char a;

    i = 0;
    if (str[i] && (str[i] == '\'' || str[i] == '\"'))
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

void    start_parsing(char *buff)
{
    int i;
    int j;

    i = 0;
    while (buff[i])
    {
        j = 0;
        while (buff[i + j] && !check_token(buff, i + j, 1) && !ft_isspace(buff[i + j]))
            j += pass_quote(&buff[i + j]);
        if (j > 0)
            insertion_end_cmd(ft_strndup(&buff[i], j), 0); //ICI C EST DU TEXT
        i += j + ft_skipspaces(&buff[i + j]);    
        j = 0;
        while (buff[i + j] && check_token(buff, i + j, 1) && !ft_isspace(buff[i + j]))
            j++;
        if (j > 0)
            insertion_end_cmd(ft_strndup(&buff[i], j), 0); //ICI C EST UN TOKEN       
        i += j + ft_skipspaces(&buff[i + j]);
    }
    give_list_token();
    print_liste_cmd();
}