/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 22:51:59 by mkane             #+#    #+#             */
/*   Updated: 2024/05/11 16:58:13 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**format_env(t_minishell *minishell);
static char	*get_access(char **env_path, char *cmd);

char	*get_path(t_minishell *minishell, char *cmd)
{
	char	*path;
	char	**path_list;
	int		i;

	if (ft_strchr(cmd, '/') != NULL)
	{
		path = ft_strdup(cmd);
		if (!path)
			return (NULL);
		return (path);
	}
	path_list = format_env(minishell);
	if (!path_list)
		return (NULL);
	i = 0;
	while (path_list[i])
	{
		path_list[i] = ft_strjoin(path_list[i], "/");
		if (!path_list[i])
			return (clear_tab(path_list), NULL);
		i++;
	}
	path = get_access(path_list, cmd);
	clear_tab(path_list);
	return (path);
}

static	char	**format_env(t_minishell *minishell)
{
	char	**split_path;
	char	*env_path;

	env_path = find_env(minishell->env, "PATH");
	if (!env_path)
		return (NULL);
	if (ft_strcmp(env_path, "") == 0)
		return (free(env_path), NULL);
	split_path = ft_split(env_path, ':');
	free(env_path);
	if (!split_path)
		return (NULL);
	return (split_path);
}

static char	*get_access(char **env_path, char *cmd)
{
	int		i;
	char	*tmp;
	char	*path;

	i = 0;
	while (env_path[i])
	{
		tmp = ft_strdup(env_path[i]);
		if (!tmp)
			return (NULL);
		path = ft_strjoin(tmp, cmd);
		if (!path)
		{
			if (tmp)
				free(tmp);
			return (NULL);
		}
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}
