/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 22:05:13 by mkane             #+#    #+#             */
/*   Updated: 2024/05/11 16:58:04 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char		**get_cmd(t_minishell *minishell);
static void		clear_execve(t_minishell *minishell);
static void		print_fail_error(char *path);

void	minishell_execve(t_minishell *minishell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd("Fork error\n", 2));
	signal(SIGINT, control_c_child);
	signal(SIGQUIT, control_back_slash_child);
	if (pid == 0)
	{
		excecute(minishell);
		clear_execve(minishell);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		get_status(WEXITSTATUS(status), 0);
	if (get_status(0, 3) == 131)
		ft_putstr_fd("Quit\n", 1);
	if (get_status(0, 3) == 130)
		ft_putstr_fd("\n", 1);
	signal(SIGINT, control_c_parent);
	signal(SIGQUIT, SIG_IGN);
}

int	excecute(t_minishell *minishell)
{
	char	*path;
	char	**cmd;
	char	**env;

	env = convert_env(minishell->env);
	if (!env)
		return (0);
	cmd = get_cmd(minishell);
	if (!cmd)
		return (clear_tab(env), 0);
	path = get_path(minishell, cmd[0]);
	if (!path)
		return (ft_putstr_fd("Command not found\n", 2), clear_tab(cmd),
			clear_tab(env), ft_exit(127, 0, 0));
	execve(path, cmd, env);
	print_fail_error(path);
	clear_tab(cmd);
	free(path);
	clear_tab(env);
	return (0);
}

static void	clear_execve(t_minishell *minishell)
{
	free_and_close(minishell);
	token_lstclear(&minishell->token);
	cmd_lstclear(&minishell->cmd);
	env_lstclear(&minishell->env);
	free(minishell->line);
	rl_clear_history();
	exit(get_status(0, 3));
}

static	void	print_fail_error(char *path)
{
	if (access(path, X_OK) == -1)
	{
		ft_putstr_fd("No such file or directory\n", 2);
		if (access(path, F_OK) == -1)
			ft_exit(127, 0, 0);
		else
			ft_exit(126, 0, 0);
	}
	else
	{
		ft_putstr_fd("Command not found\n", 2);
		ft_exit(126, 0, 0);
	}
}

static char	**get_cmd(t_minishell *minishell)
{
	t_cmd	*cmds;
	char	**cmd;
	int		i;

	cmds = minishell->cmd;
	i = cmd_lstsize(cmds);
	cmd = ft_calloc(i + 1, sizeof(char *));
	if (!cmd)
		return (NULL);
	i = 0;
	while (cmds)
	{
		cmd[i] = ft_strdup(cmds->cmd);
		if (!cmd[i])
			return (clear_tab(cmd), NULL);
		i++;
		cmds = cmds->next;
	}
	cmd[i] = NULL;
	return (cmd);
}
