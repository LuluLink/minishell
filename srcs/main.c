#include "minishell.h"

int main(int ac, char **av, char **envp)
{
       char    *buff;
       (void)ac;
       (void)av;
       (void)envp;

       initialisation_struct();
       init_liste_env(envp); //initialisation de la liste chaine env
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