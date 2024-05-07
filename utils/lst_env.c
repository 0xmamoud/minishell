/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:25:29 by mkane             #+#    #+#             */
/*   Updated: 2024/05/07 20:49:53 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*env_lstnew(char *name, char *content)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->content = ft_strdup(content);
	if (!new->content)
	{
		free(new);
		return (NULL);
	}
	new->name = ft_strdup(name);
	if (!new->name)
	{
		free(new->content);
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

t_env	*env_lstlast(t_env *env)
{
	t_env	*tmp;

	if (!env)
		return (NULL);
	tmp = env;
	while (tmp->next && tmp)
		tmp = tmp->next;
	return (tmp);
}

void	env_lstadd_back(t_env **env, t_env *new)
{
	t_env	*tmp;

	tmp = NULL;
	if (!env || !new)
		return ;
	if (!*env)
	{
		*env = new;
		return ;
	}
	tmp = env_lstlast(*env);
	if (!tmp)
		return ;
	tmp->next = new;
}

void	env_lstdelnode(t_env **env, char *name)
{
	t_env	*tmp;
	t_env	*prev;

	if (!*env)
		return ;
	tmp = *env;
	if (!ft_strcmp(tmp->name, name))
	{
		*env = (*env)->next;
		free(tmp->name);
		free(tmp->content);
		free(tmp);
		return ;
	}
	while (tmp && ft_strcmp(tmp->name, name) != 0)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return ;
	prev->next = tmp->next;
	free(tmp->name);
	free(tmp->content);
	free(tmp);
}

void	env_lstclear(t_env **env)
{
	t_env	*tmp;

	if (!*env)
		return ;
	while (*env)
	{
		tmp = (*env)->next;
		free((*env)->name);
		free((*env)->content);
		free(*env);
		*env = tmp;
	}
}
