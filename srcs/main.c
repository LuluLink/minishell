#include "minishell.h"

int main(int ac, char **av, char **envp)
{
       initialisation_struct(&g_all);

       while(42)
       {
              ft_putstr("$>");
              get_next_line(0);
       }
}