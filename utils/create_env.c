/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:43:45 by mkane             #+#    #+#             */
/*   Updated: 2024/04/20 23:00:46 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	classic_env(t_minishell *minishell, char **envp)
{
	int		j;
	char	*name;
	char	*content;
	t_env	*new;

	int (i) = -1;
	while (envp[++i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		name = ft_substr(envp[i], 0, j);
		if (!name)
			return (0);
		content = ft_strdup(envp[i] + j + 1);
		if (!content)
			return (free(name), 0);
		new = env_lstnew(name, content);
		free(name);
		free(content);
		if (!new)
			return (0);
		env_lstadd_back(&minishell->env, new);
	}
	return (1);
}

static int	fake_env(t_minishell *minishell)
{
	t_env	*one;
	t_env	*two;
	t_env	*three;
	t_env	*four;

	one = env_lstnew("PWD", "/home/mkane");
	if (!one)
		return (0);
	env_lstadd_back(&minishell->env, one);
	two = env_lstnew("SHLVL", "1");
	if (!two)
		return (0);
	env_lstadd_back(&minishell->env, two);
	three = env_lstnew("_", "/usr/bin/env");
	if (!three)
		return (0);
	env_lstadd_back(&minishell->env, three);
	four = env_lstnew("PATH",
			"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
	if (!four)
		return (0);
	env_lstadd_back(&minishell->env, four);
	return (1);
}

int	create_env(char **envp, t_minishell *minishell)
{
	if (!envp || !*envp)
	{
		minishell->env_ignore = 1;
		if (!fake_env(minishell))
			return (0);
	}
	else
	{
		minishell->env_ignore = 0;
		if (!classic_env(minishell, envp))
			return (0);
	}
	return (1);
}

char	*find_env(t_env *env, char *name)
{
	t_env	*tmp;
	char	*content;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, name, ft_strlen(name)))
		{
			content = ft_strdup(tmp->content);
			if (!content)
				return (NULL);
			return (content);
		}
		tmp = tmp->next;
	}
	return (NULL);
}