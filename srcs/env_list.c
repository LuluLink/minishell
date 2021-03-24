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

void    free_list_env()
{
    t_elem_env *tmp;
    tmp = g_all.first_env;
    while (tmp != NULL)
    {
        free(tmp->env);
        g_all.first_env = g_all.first_env->next;
        free(tmp);
        tmp = g_all.first_env;
    }
    //free(g_all.first_env);
}

void    insertion_end_env(char *str)
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
    nouveau->prev = tmp;
}

void    initialisation_env(char *str)
{
   // g_all.first_env = malloc(sizeof(char*)); //malloc le pointeur
    t_elem_env *nouveau = malloc(sizeof(*nouveau)); //malloc la structure

    nouveau->env = str;
    nouveau->next = NULL; //premier élément donc pas de next ou previous
    nouveau->prev = NULL;
    g_all.first_env = nouveau; //le pointeur first_env pointe sur la premiere struct
}

void    init_liste_env(char **envp)
{
    int i;
    char *tmp;

	i = 1;
    tmp = ft_strdup(envp[0]);
    initialisation_env(tmp); //init du pointeur sur le premier élément de la liste env
	while (envp[i] != NULL)
	{
        tmp = ft_strdup(envp[i]);
		insertion_end_env(tmp); //ajout nouvelle élément a la fin de la liste env
		i++;
	}
}