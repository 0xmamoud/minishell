/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:43:44 by mkane             #+#    #+#             */
/*   Updated: 2024/05/09 17:03:48 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	pipe_init_redirection(t_pipe_cmds **cmds, t_minishell *minishell)
{
	(void)minishell;
	if ((*cmds)->in.file)
	{
		(*cmds)->in.fd = open((*cmds)->in.file, O_RDONLY);
		if ((*cmds)->in.fd == -1)
		{
			perror((*cmds)->in.file);
			return (ft_exit(1, 0, 0));
		}
		if (dup2((*cmds)->in.fd, STDIN_FILENO) == -1)
			return (ft_exit(1, 0, 0));
		close((*cmds)->in.fd);
	}
	if ((*cmds)->out.file)
	{
		if ((*cmds)->out.type == REDIR_OUT)
			(*cmds)->out.fd = open((*cmds)->out.file,
					O_WRONLY | O_CREAT | O_TRUNC, 0777);
		else
			(*cmds)->out.fd = open((*cmds)->out.file,
					O_WRONLY | O_CREAT | O_APPEND, 0777);
		if ((*cmds)->out.fd == -1)
		{
			perror((*cmds)->out.file);
			if ((*cmds)->in.fd != -1)
				close((*cmds)->in.fd);
			return (ft_exit(1, 0, 0));
		}
		if (dup2((*cmds)->out.fd, STDOUT_FILENO) == -1)
			return (ft_exit(1, 0, 0));
		close((*cmds)->out.fd);
	}
	return (1);
}

static void	pipe_expend_bultin(t_minishell *minishell, t_pipe_cmds *cmds)
{
	if (cmds->type == ECHO)
		return (echo(minishell));
	if (cmds->type == CD)
	{
		cd(minishell);
		return ;
	}
	if (cmds->type == PWD)
		return (pwd());
	if (cmds->type == EXPORT)
		return (export(minishell));
	if (cmds->type == UNSET)
		return (unset(minishell));
	if (cmds->type == ENV)
		return (env(minishell));
	if (cmds->type == EXIT)
		return (exit_minishell(minishell));
	excecute(minishell);
}

static void	pipe_child_process(t_minishell *minishell, t_pipe_cmds **cmds)
{
	if ((*cmds)->index != 0)
		dup2(minishell->pipe.prev_fd, STDIN_FILENO);
	if ((*cmds)->index != minishell->pipe.len_pid - 1)
		dup2(minishell->pipe.fd[1], STDOUT_FILENO);
	if (minishell->pipe.prev_fd != -1)
		close(minishell->pipe.prev_fd);
	close(minishell->pipe.fd[0]);
	close(minishell->pipe.fd[1]);
	if (!pipe_init_redirection(cmds, minishell))
	{
		ft_exit(1, 0, 0);
		return ;
	}
	pipe_expend_bultin(minishell, *cmds);
}

static int	pipe_process(t_minishell *minishell, t_pipe_cmds **cmds)
{
	if (pipe(minishell->pipe.fd) == -1)
		return (ft_putstr_fd("pipe error\n", 2), ft_exit(1, 0, 0));
	minishell->pipe.pid[(*cmds)->index] = fork();
	if (minishell->pipe.pid[(*cmds)->index] == -1)
		return (ft_putstr_fd("fork error\n", 2), ft_exit(1, 0, 0));
	signal(SIGINT, control_c_child);
	signal(SIGQUIT, control_back_slash_child);
	if (minishell->pipe.pid[(*cmds)->index] == 0)
	{
		//printf("CMD: %s\n", (*cmds)->cmd);
		if ((*cmds)->cmd[0] != '\0')
			pipe_child_process(minishell, cmds);
		if (minishell->pipe.prev_fd != -1)
			close(minishell->pipe.prev_fd);
		pipe_lstclear(&minishell->pipe.cmds);
		cmd_lstclear(&minishell->cmd);
		token_lstclear(&minishell->token);
		env_lstclear(&minishell->env);
		free(minishell->pipe.pid);
		free(minishell->line);
		rl_clear_history();
		ft_exit(get_status(0, 3), 1, 1);
	}
	else
	{
		if (minishell->pipe.prev_fd != -1)
			close(minishell->pipe.prev_fd);
		minishell->pipe.prev_fd = minishell->pipe.fd[0];
		close(minishell->pipe.fd[1]);
	}
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

static void pipi_open_heredocs(t_minishell *minishell)
{
	t_pipe_cmds	*cmds;

	cmds = minishell->pipe.cmds;
	while (cmds)
	{
		if (cmds->in.type == HEREDOC)
		{
			ft_here_doc(&cmds->in.file, minishell);
		}
		cmds = cmds->next;
	}
}


void	minishell_pipe(t_minishell *minishell)
{
	int		i;
	int		status;

	i = 0;
	(void)status;
	minishell->in.fd = -1;
	minishell->out.fd = -1;
	minishell->in.type = -1;
	minishell->out.type = -1;
	minishell->in.file = NULL;
	minishell->out.file = NULL;
	minishell->pipe.prev_fd = -1;
	if (!init_pipe(minishell))
		return (ft_exit(1, 0, 0), pipe_lstclear(&minishell->pipe.cmds));
	minishell->pipe.len_pid = pipe_lstlast(minishell->pipe.cmds)->index + 1;
	if (!pipe_redirection(minishell))
		return (pipe_lstclear(&minishell->pipe.cmds));
	if (!pipe_types(minishell))
		return (ft_exit(1, 0, 0), pipe_lstclear(&minishell->pipe.cmds));
	pipi_open_heredocs(minishell);
	minishell->pipe.pid = malloc(sizeof(pid_t) * minishell->pipe.len_pid);
	if (!pipe_loop(minishell))
	{
		if (minishell->pipe.prev_fd != -1)
		close(minishell->pipe.prev_fd);
		free(minishell->pipe.pid);
		pipe_lstclear(&minishell->pipe.cmds);
		ft_exit(1, 0, 0);
		return ;
	}
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
