#include "minishell.h"


int     verif_end_backslash(char *line)
{
    int i;
    int verif;

    i = 0;
    verif = 0;
    while (line[i] != '\0')
        i++;
    if (line[i - 1] == '\\')
    {
        while (line[i - 1] == '\\')
        {
            verif++;
            i--;
        }
    }
    verif = verif % 2;
    if (verif == 1)
        return (-1);
    return (0);
}

void    verif_backslash_quote(char *line, int i)
{
    int backslash;

    backslash = 0;
    while (i >= 0 && line [i] == '\\')
    {
        backslash++;
        i--;
    }
    backslash = backslash % 2;
    if (backslash == 0 && g_all.quote == 0)
    {
        g_all.quote = 1;
        return ;
    }
        if (backslash == 0 && g_all.quote == 1)
    {
        g_all.quote = 0;
        return ;
    }
}  

void    verif_backslash_dquote(char *line, int i)
{
    int backslash;

    backslash = 0;
    while (i >= 0 && line [i] == '\\')
    {
        backslash++;
        i--;
    }
    backslash = backslash % 2;
    if (backslash == 0 && g_all.d_quote == 0)
    {
        g_all.d_quote = 1;
        return ;
    }
        if (backslash == 0 && g_all.d_quote == 1)
    {
        g_all.d_quote = 0;
        return ;
    }
}

int verif_quote(char *line)
{
    int i;
    
    i = 0;
    g_all.d_quote = 0;
    g_all.quote = 0;
    while (line[i] != '\0')
    {
        if ((line[i] == '\"' && g_all.d_quote == 0 && i == 0) ||
            (line[i] == '\"' && g_all.d_quote == 0 && line[i - 1] != '\\'))
            g_all.d_quote = 1;
        else if (line[i] == '\"' && g_all.d_quote == 1 && line[i - 1] != '\\')
            g_all.d_quote = 0;
        if ((line[i] == '\'' && g_all.quote == 0 && i == 0) ||
            (line[i] == '\'' && g_all.quote == 0 && line[i - 1] != '\\'))
            g_all.quote = 1;
        else if (line[i] == '\'' && g_all.quote == 1 && line[i - 1] != '\\')
            g_all.quote = 0;
        if (i != 0 && line[i] == '\'' && line[i - 1] == '\\')
            verif_backslash_quote(line, i - 1);
        if (i != 0 && line[i] == '\"' && line[i - 1] == '\\')
            verif_backslash_dquote(line, i - 1);
        i++;
    }
    if (g_all.quote == 1 || g_all.d_quote == 1)
        return (-1);
    return (0);
}