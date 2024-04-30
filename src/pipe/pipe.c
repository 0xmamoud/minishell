/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:43:44 by mkane             #+#    #+#             */
/*   Updated: 2024/04/30 23:22:46 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	setup_commands(t_minishell *minishell, char **args)
{
	t_cmd	*new;
	int		i;

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
		return (0);
	return (1);
}

// static int	pipe_init_redirection(t_pipe_cmds *cmds)
// {
// 	if (cmds->in.type == HEREDOC)
// 		ft_here_doc(&cmds->in.file);
// 	if (cmds->in.type == REDIR_IN || cmds->in.type == HEREDOC)
// 	{
// 		cmds->in.fd = open(cmds->in.file, O_RDONLY);
// 		if (cmds->in.fd == -1)
// 		{
// 			ft_putstr_fd("No such file or directory\n", 2);
// 			return (ft_exit(1, 0, 0));
// 		}
// 	}
// 	if (cmds->out.type == REDIR_OUT || cmds->out.type == REDIR_OUT_APPEND)
// 	{
// 		if (cmds->out.type == REDIR_OUT)
// 			cmds->out.fd = open(cmds->out.file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
// 		else
// 			cmds->out.fd = open(cmds->out.file, O_WRONLY | O_CREAT | O_APPEND, 0777);
// 		if (cmds->out.fd == -1)
// 		{
// 			ft_putstr_fd("No such file or directory\n", 2);
// 			close(cmds->in.fd);
// 			if (cmds->in.type == HEREDOC)
// 				unlink(cmds->in.file);
// 			return (ft_exit(1, 0, 0));
// 		}
// 	}
// 	return (1);
// }

static void	pipe_expend_bultin(t_minishell *minishell, t_pipe_cmds *cmds)
{
	if (cmds->type == ECHO)
		return (echo(minishell));
	if (cmds->type == CD)
		return (cd(minishell));
	if (cmds->type == PWD)
		return (pwd(minishell));
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

static void	pipe_child_process(t_minishell *minishell, t_pipe_cmds *cmds)
{
	if (cmds->index != 0)
		dup2(minishell->pipe.prev_fd, STDIN_FILENO);
	if (cmds->index != minishell->pipe.len_pid - 1)
		dup2(minishell->pipe.fd[1], STDOUT_FILENO);
	close(minishell->pipe.fd[0]);
	close(minishell->pipe.fd[1]);
	// if (!pipe_init_redirection(cmds))
	// {
	// 	ft_exit(1, 0, 0);
	// 	return ;
	// }
	pipe_expend_bultin(minishell, cmds);
}

static int	pipe_process(t_minishell *minishell, t_pipe_cmds *cmds)
{
	if (pipe(minishell->pipe.fd) == -1)
		return (ft_putstr_fd("pipe error\n", 2), ft_exit(1, 0, 0));
	minishell->pipe.pid[cmds->index] = fork();
	if (minishell->pipe.pid[cmds->index] == -1)
		return (ft_putstr_fd("fork error\n", 2), ft_exit(1, 0, 0));
	signal(SIGINT, control_c_child);
	signal(SIGQUIT, control_back_slash_child);
	if (minishell->pipe.pid[cmds->index] == 0)
	{
		pipe_child_process(minishell, cmds);
		token_lstclear(&minishell->token);
		pipe_lstclear(&minishell->pipe.cmds);
		cmd_lstclear(&minishell->cmd);
		env_lstclear(&minishell->env);
		free(minishell->pipe.pid);
		free(minishell->line);
		ft_exit(1, 1, 1);
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
		if (!pipe_process(minishell, cmds))
			return (cmd_lstclear(&minishell->cmd), 0);
		cmd_lstclear(&minishell->cmd);
		minishell->cmd = NULL;
		cmds = cmds->next;
	}
	return (1);
}


void	minishell_pipe(t_minishell *minishell)
{
	int		i;
	int		status;

	i = 0;
	if (!init_pipe(minishell))
		return (pipe_lstclear(&minishell->pipe.cmds));
	if (!pipe_redirection(minishell))
		return (pipe_lstclear(&minishell->pipe.cmds));
	if (!pipe_types(minishell))
		return (pipe_lstclear(&minishell->pipe.cmds));
	minishell->pipe.len_pid = pipe_lstlast(minishell->pipe.cmds)->index + 1;
	minishell->pipe.pid = malloc(sizeof(pid_t) * minishell->pipe.len_pid);
	minishell->pipe.prev_fd = -1;
	pipe_loop(minishell);
	while (i < minishell->pipe.len_pid)
	{
		waitpid(minishell->pipe.pid[i], &status, 0);
		if (WIFEXITED(status))
			minishell->status = WEXITSTATUS(status);
		i++;
	}
	signal(SIGINT, control_c_parent);
	signal(SIGQUIT, SIG_IGN);
	if (minishell->pipe.prev_fd != -1)
		close(minishell->pipe.prev_fd);
	free(minishell->pipe.pid);
	pipe_lstclear(&minishell->pipe.cmds);
}
