/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacorrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 12:04:36 by pacorrei          #+#    #+#             */
/*   Updated: 2021/03/28 11:03:38 by pacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_liste_env(void)
{
	t_elem_env *actuel;

	actuel = g_all.first_env;
	while (actuel != NULL)
	{
		printf("%s\n", actuel->env);
		actuel = actuel->next;
	}
}

void	free_list_env_sort(t_elem_env *lst)
{
	t_elem_env *tmp;

	tmp = lst;
	while (tmp)
	{
		free(tmp->env);
		lst = lst->next;
		free(tmp);
		tmp = lst;
	}
}

void	free_list_env(void)
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
}

void	insertion_end_env(char *str)
{
	t_elem_env *nouveau;
	t_elem_env *tmp;

	nouveau = malloc(sizeof(t_elem_env));
	tmp = g_all.first_env;
	nouveau->env = str;
	if (tmp->next == NULL)
	{
		tmp->next = nouveau;
		nouveau->next = NULL;
		nouveau->prev = g_all.first_env;
		return ;
	}
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = nouveau;
	nouveau->next = NULL;
	nouveau->prev = tmp;
}

void	initialisation_env(char *str)
{
	t_elem_env *nouveau;

	nouveau = malloc(sizeof(t_elem_env));
	nouveau->env = str;
	nouveau->next = NULL;
	nouveau->prev = NULL;
	g_all.first_env = nouveau;
}

void	init_liste_env(char **envp)
{
	int		i;
	char	*tmp;

	i = 1;
	tmp = ft_strdup(envp[0]);
	initialisation_env(tmp);
	while (envp[i] != NULL)
	{
		tmp = ft_strdup(envp[i]);
		insertion_end_env(tmp);
		i++;
	}
}
