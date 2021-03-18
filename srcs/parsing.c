#include "minishell.h"

char    *check_quote(char *str, char *str2, int *k)
{
    int     i;
    int     j;
    char *test;

    i = 0;
    j = 0;
    if (str[i] == '\'')
    {
        i++;
        while (str[i] && str[i] != '\'')
        {
            i++;
            printf("i : %d, str[i] : %c\n", i, str[i]);
        }
        if (!str[i])
        {
            printf("failed : |%c|\n", str[i]);
            return (NULL);
        }
        str2 = ft_strnjoin(str2, str, i);
        i++;
    }
    else if (str[i] == '\"')
    {
        i++;
        while (str[i] && str[i] != '$' && str[i] != '\"')
            i++;
        printf("iii : %d\n", i);
        str2 = ft_strnjoin(str2, str, (str[i] == '\"') ? i += 1 : i);
        printf("iii : %d\n", i);
        if (str[i] == '$')
        {
            while (!ft_isspace(str[i + j]) && str[i + j] != '\"')
                j++;
            str2 = ft_strjoin(str2, (char *)chrenv(test = ft_strndup(&str[i + 1], j - 1)));
            free(test);
        }
    }
    printf("i (in function) : %d\nstr : |%s|\n", i + j, str2);
    *k += i + j;
    return (str2);
}

int     check_token(char a)
{
    if (a == '<' || a == '>' || a == '|' || a == '\'' || a == '\"' || a == '$' || a == ';')
    {
        return (1);
    }
    return (0);
}

void    start_parsing(char *buff)
{
    int i;
    int j;
    char *test = ft_strdup("");

    i = 0;
    while (buff[i])
    {
        j = 0;
        printf("i : %d\n", i);
        while (!check_token(buff[i + j]))
            j++;
        if (j > 0)
            test = ft_strnjoin(test, buff, i + j);
        i = i + j;
        printf("i : %d\n", i);
        test = check_quote(&buff[i], test, &i);
    }
    printf("string final : |%s|\n", test);
}