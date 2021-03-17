int    check_quote(char *str, char *str2)
{
    int     i;
    char    a;
    int     j;

    i = 0;
    j = 0;
    if (str[i] == '\'')
    {
        while (str[i] && str[i] != '\'')
            i++;
        if (!str[i])
            return (-1);
        ft_strnjoin(str2, str, i);
    }
    else if (str[i] == '\"')
    {
        while (str[i] && str[i] != '$')
            i++;
        ft_strnjoin(str2, str, i);
        if (str[i] == '$')
            while (!ft_isspace(str[i + j]))
                j++;
    }
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

    i = 0;
    while (buff[i])
    {
        i = 2;
    }
}