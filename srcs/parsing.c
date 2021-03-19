#include "minishell.h"

char    *ft_quote(char *str, int *k, char a)
{
    int i;

    i = 1;
    if (a == '\'')
    {
        while (str[i] && (str[i] != '\'' || str[i - 1] == '\\'))
            i++;
        *k += (str[i]) ? i += 1 : i;
        printf("str : |%s|\n", ft_strndup(str, i));
        return (ft_strndup(str, i));
    }
    return (NULL);
}

/*

** check_token check si le char envoyé est un tocken " ' | < > $
** si i vaut 0 il check tous les tokens
** si i vaut 1 il ne check que les separateurs

*/

int     check_token(char str, int i)
{
    if (i == 0)
        if (str == '<' || str == '>' || str == '|' || str == '\'' || str == '\"' || str == '$' || str == ';')
            return (1);
    if (i == 1)
        if (str == '<' || str == '>' || str == '|' || str == ';')
            return (1);
    return (0);
}

void    start_parsing(char *buff)
{
    int i;
    char *str = ft_strdup("");

    i = 0;
    while (buff[i])
    {
        if (!check_token(buff[i], 0))
        {
            str = ft_strjoinchar(str, buff[i]);
            while (ft_isspace(buff[i + 1]) && ft_isspace(buff[i]))
                i++;
        }
        else 
        {
            str = (i > 0 && !ft_isspace(buff[i - 1] && check_token(buff[i], 1)) ? ft_strjoinchar(str, ' ') : str);
            if (buff[i] == '\'' || buff[i] == '\"')
                str = ft_strjoin(str, ft_quote(&buff[i], &i, buff[i]));
            else 
                str = ft_strjoinchar(str, buff[i]);
            str = (buff[i] && !ft_isspace(buff[i + 1] && check_token(buff[i], 1)) ? ft_strjoinchar(str, ' ') : str);
        }
        //if (ft_isspace(buff[i]))
        //    while (ft_isspace(buff[i]))
        //        i++;
        if (buff[i])
          i++;
    }
    printf("test : \"%s\"\n", str);
}