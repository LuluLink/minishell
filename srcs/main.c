#include "minishell.h"

int main(int ac, char **av, char **envp)
{
       (void)ac;
       (void)av;
       (void)envp;

       initialisation_struct();
       init_liste_env(envp); //initialisation de la liste chaine env
       write(1, "$> ", 3); //printf est trop lent
       while (get_next_line(&g_all.buff) > 0)
       {      
              if (((verif_quote(g_all.buff) == 0)) && (verif_end_backslash(g_all.buff) == 0))
                     start_parsing(g_all.buff);
              else if ((verif_quote(g_all.buff) == -1))
                     ft_putstr_fd("Error : quote not closed\n", 2);
              else if ((verif_end_backslash(g_all.buff) == -1))
                     ft_putstr_fd("Error : multiligne with '\\' \n", 2);
              write(1, "$> ", 3);
              free_list_cmd();
              free(g_all.buff);
       }
       free_list_cmd();
       free_list_env();
       free(g_all.buff);
       return(0);
}