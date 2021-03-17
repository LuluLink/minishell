#include "minishell.h"

int main(int ac, char **av, char **envp)
{
       char    *buff;

       initialisation_struct(&g_all);
       init_liste_env(envp, &g_all); //initialisation de la liste chaine env
       print_liste_env(&g_all);
       write(1, "$> ", 3); //printf est trop lent
       while (get_next_line(&buff) > 0)
       {
              start_parsing(buff);
              write(1, "$> ", 3);
              free(buff);
       }
       free(buff);
       return(0);
}