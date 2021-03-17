#include "minishell.h"
void    print_liste_env()
{
    t_elem_env *actuel = g_all.first_env;

    while (actuel != NULL)
    {
        printf("%s\n", actuel->env);
        actuel = actuel->next;
    }
}

void    insertion_end_env(, char *str)
{
    t_elem_env *nouveau = malloc(sizeof(*nouveau));
    t_elem_env *tmp = g_all.first_env;
    nouveau->env = str;
    if (tmp->next == NULL) // si c'est le deuxième élément de la chaine 
    {
        tmp->next = nouveau;
        nouveau->next = NULL;
        nouveau->prev = g_all.first_env;
        return ;
    }
    while(tmp->next != NULL)// on parcourt la liste pour allez au dernier élément
    {
        tmp = tmp->next;
    }
    tmp->next = nouveau;//l'avant dernier pointe sur le dernier
    nouveau->next = NULL;
    nouveau->prev = tmp->prev->next;
}

void    initialisation_env(char *str)
{
    g_all.first_env = malloc(sizeof(char*)); //malloc le pointeur
    t_elem_env *elem = malloc(sizeof(*elem)); //malloc la structure

    elem->env = str;
    elem->next = NULL; //premier élément donc pas de next ou previous
    elem->prev = NULL;
    g_all.first_env = elem; //le pointeur first_env pointe sur la premiere struct
}

void    init_liste_env(char **envp)
{
    int i;

	i = 1;
    initialisation_env(envp[0], g_all); //init du pointeur sur le premier élément de la liste env
	while (envp[i] != NULL)
	{
		insertion_end_env(g_all, envp[i]); //ajout nouvelle élément a la fin de la liste env
		i++;
	}
}