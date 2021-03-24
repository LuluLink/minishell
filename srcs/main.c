#include "minishell.h"

int main(int ac, char **av, char **envp)
{
      // char    *buff;
       (void)ac;
       (void)av;
       (void)envp;

       initialisation_struct();
       init_liste_env(envp); //initialisation de la liste chaine env
       write(1, NEWLINE, ft_strlen(NEWLINE)); //printf est trop lent
       // \e[38;5;164m \e[0m

       while (get_next_line(&g_all.buff) > 0)
       {      
              if (((verif_quote(g_all.buff) == 0)) && (verif_end_backslash(g_all.buff) == 0))
                     start_parsing(g_all.buff);
              else if ((verif_quote(g_all.buff) == -1))
                     ft_putstr_fd("Error : quote not closed\n", 2);
              else if ((verif_end_backslash(g_all.buff) == -1))
                     ft_putstr_fd("Error : multiligne with '\\' \n", 2);
              write(1, NEWLINE, ft_strlen(NEWLINE));
              free_list_cmd();
              free(g_all.buff);
       }
       free_list_cmd();
       free_list_env();
       free(g_all.buff);
       return(0);
}