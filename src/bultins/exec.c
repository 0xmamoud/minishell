/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 22:05:13 by mkane             #+#    #+#             */
/*   Updated: 2024/04/25 15:43:49 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char		**get_cmd(t_minishell *minishell);
static char		*get_access(char **env_path, char *cmd);
static char		*get_path(t_minishell *minishell, char *cmd);
static int		excecute(t_minishell *minishell);

void	minishell_execve(t_minishell *minishell)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd("Fork error\n", 2));
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (pid == 0)
	{
		interactive_mode();
		if (!redirection(minishell))
			ft_exit(minishell, 1, 1, 1);
		if (!init_files(minishell))
		{
			free_and_close(minishell);
			ft_exit(minishell, 121, 1, 1);
		}
		if (!excecute(minishell))
		{
			free_and_close(minishell);
			token_lstclear(&minishell->token);
			env_lstclear(&minishell->env);
			free(minishell->line);
			ft_exit(minishell, 1, 1, 1);
		}
	}
	else
		waitpid(pid, NULL, 0);
}

static int	excecute(t_minishell *minishell)
{
	char	*path;
	char	**cmd;
	char	**env;

	env = convert_env(minishell->env);
	if (!env)
		return (0);
	cmd = get_cmd(minishell);
	if (!cmd)
		return (clear_tab(env),0);
	path = get_path(minishell, cmd[0]);
	if (!path)
	{
		clear_tab(cmd);
		clear_tab(env);
		return (ft_putstr_fd("Command not found\n", 2), ft_exit(minishell, 127, 0, 0));
	}
	if (execve(path, cmd, env) == -1)
	{
		clear_tab(cmd);
		free(path);
		clear_tab(env);
		return (ft_putstr_fd("Command not found\n", 2), ft_exit(minishell, 127, 0, 0));
	}
	return (1);
}

static char	**get_cmd(t_minishell *minishell)
{
	t_token	*token;
	char	**cmd;
	int		i;

	token = minishell->token;
	i = 0;
	cmd = (char **)malloc(sizeof(char *) * (cmd_len(minishell) + 1));
	if (!cmd)
		return (NULL);
	while (token)
	{
		if (token->type == COMMAND)
		{
			cmd[i] = ft_strdup(token->cmd);
			if (!cmd[i])
				return (clear_tab(cmd), NULL);
			i++;
		}
		token = token->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

static char	*get_path(t_minishell *minishell, char *cmd)
{
	char	*env_path;
	char	*path;
	char	**split_env;
	int		i;

	if (ft_strchr(cmd, '/') != NULL)
	{
		path = ft_strdup(cmd);
		if (!path)
			return (NULL);
		return (path);
	}
	env_path = find_env(minishell->env, "PATH");
	if (!env_path)
		return (NULL);
	if (ft_strncmp(env_path, "", ft_strlen(env_path)) == 0)
		return (free(env_path), NULL);
	split_env = ft_split(env_path, ':');
	if (!split_env)
		return (free(env_path), NULL);
	free(env_path);
	i = 0;
	while (split_env[i])
	{
		split_env[i] = ft_strjoin(split_env[i], "/");
		if (!split_env[i])
			return (clear_tab(split_env), NULL);
		i++;
	}
	path = get_access(split_env, cmd);
	clear_tab(split_env);
	return (path);
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