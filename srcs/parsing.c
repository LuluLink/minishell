#include "minishell.h"

int    check_quote(char *str, char *str2)
{
    int     i;
    char    a;
    int     j;
    char *test;

    i = 0;
    j = 0;
    printf("str  : |%s|\nstr2 : |%s|\n", str, str2);
    if (str[i] == '\'')
    {
        printf("im in\n");
        while (str[i] && str[i] != '\'')
            i++;
        if (!str[i])
            return (-1);
        ft_strnjoin(str2, str, i);
    }
    else if (str[i] == '\"')
    {
        printf("im in2\n");
        while (str[i] && str[i] != '$')
            i++;
        ft_strnjoin(str2, str, i);
        if (str[i] == '$')
        {
            while (!ft_isspace(str[i + j]) && str[i + j] != '\"')
                j++;
            ft_strjoin(str2, (char *)chrenv(test = ft_strndup(&str[i + 1], j - 1)));
            free(test);
        }
    }
    return (i + j);
}

int     check_token(char *str)
{
    int i;

    i = 0;
    if (str[i] == '<' || str[i] == '>' || str[i] == '|')
    {
        if (str[i] == '>' && str[i + 1] && str[i + 1] == '>')
            i++;
    }
    return 0;
}

void    start_parsing(char *buff)
{
    int i;
    char *test = ft_strdup("");

    i = 0;
    while (buff[i])
    {
        check_quote(&buff[i], test);
        i++;
    }
    printf("test : \"%s\"\n", test);
}