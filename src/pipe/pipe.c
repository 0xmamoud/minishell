/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:43:44 by mkane             #+#    #+#             */
/*   Updated: 2024/05/13 21:32:16 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pipe_parse(t_minishell *minishell);
static int	pipe_loop(t_minishell *minishell);
static int	setup_commands(t_minishell *minishell, char **args);
static void	pipe_waitpid(t_minishell *minishell);

void	minishell_pipe(t_minishell *minishell)
{
	if (!pipe_parse(minishell))
		return ;
	pipe_open_heredocs(minishell);
	minishell->pipe.pid = malloc(sizeof(pid_t) * minishell->pipe.len_pid);
	if (get_status(0, 3) == 130)
	{
		pipe_lstclear(&minishell->pipe.cmds);
		if (minishell->pipe.prev_fd != -1)
			close(minishell->pipe.prev_fd);
		free(minishell->pipe.pid);
		return ;
	}
	if (!pipe_loop(minishell))
	{
		if (minishell->pipe.prev_fd != -1)
			close(minishell->pipe.prev_fd);
		free(minishell->pipe.pid);
		pipe_lstclear(&minishell->pipe.cmds);
		ft_exit(1, 0, 0);
		return ;
	}
	pipe_waitpid(minishell);
}

static int	pipe_parse(t_minishell *minishell)
{
	minishell->in.fd = -1;
	minishell->out.fd = -1;
	minishell->in.type = -1;
	minishell->out.type = -1;
	minishell->in.file = NULL;
	minishell->out.file = NULL;
	minishell->pipe.prev_fd = -1;
	if (!init_pipe(minishell))
		return (ft_exit(1, 0, 0), pipe_lstclear(&minishell->pipe.cmds), 0);
	minishell->pipe.len_pid = pipe_lstlast(minishell->pipe.cmds)->index + 1;
	if (!pipe_redirection(minishell))
		return (pipe_lstclear(&minishell->pipe.cmds), 0);
	if (!pipe_types(minishell))
		return (ft_exit(1, 0, 0), pipe_lstclear(&minishell->pipe.cmds), 0);
	return (1);
}

static int	pipe_loop(t_minishell *minishell)
{
	t_pipe_cmds	*cmds;
	char		**args;

	args = NULL;
	cmds = minishell->pipe.cmds;
	while (cmds)
	{
		args = ft_split(cmds->cmd, ' ');
		if (!args)
			return (0);
		if (!setup_commands(minishell, args))
		{
			clear_tab(args);
			return (0);
		}
		clear_tab(args);
		if (!pipe_process(minishell, &cmds))
			return (cmd_lstclear(&minishell->cmd), 0);
		cmd_lstclear(&minishell->cmd);
		minishell->cmd = NULL;
		cmds = cmds->next;
	}
	return (1);
}

static int	setup_commands(t_minishell *minishell, char **args)
{
	t_cmd	*new;
	int		i;

	new = NULL;
	i = 0;
	while (args[i])
	{
		new = cmd_lstnew(args[i]);
		if (!new)
			return (0);
		cmd_lstadd_back(&minishell->cmd, new);
		i++;
	}
	if (!minishell->cmd)
	{
		new = cmd_lstnew("");
		if (!new)
			return (0);
		cmd_lstadd_back(&minishell->cmd, new);
		return (1);
	}
	return (1);
}

static void	pipe_waitpid(t_minishell *minishell)
{
	int		i;
	int		status;

	i = 0;
	while (i < minishell->pipe.len_pid)
	{
		waitpid(minishell->pipe.pid[i], &status, 0);
		if (WIFEXITED(status))
			get_status(WEXITSTATUS(status), 0);
		i++;
	}
	signal(SIGINT, control_c_parent);
	signal(SIGQUIT, SIG_IGN);
	if (minishell->pipe.prev_fd != -1)
		close(minishell->pipe.prev_fd);
	free(minishell->pipe.pid);
	pipe_lstclear(&minishell->pipe.cmds);
}
