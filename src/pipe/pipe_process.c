/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 20:40:27 by mkane             #+#    #+#             */
/*   Updated: 2024/05/13 21:32:33 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pipe_child_process(t_minishell *minishell, t_pipe_cmds **cmds);
static void	clear_process(t_minishell *minishell);
static void	pipe_expend_bultin(t_minishell *minishell, t_pipe_cmds *cmds);

int	pipe_process(t_minishell *minishell, t_pipe_cmds **cmds)
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
		pipe_child_process(minishell, cmds);
		clear_process(minishell);
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
	if (!pipe_outfile_redirection(cmds) || !pipe_infile_redirection(cmds))
		return ;
	pipe_expend_bultin(minishell, *cmds);
}

static	void	clear_process(t_minishell *minishell)
{
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
