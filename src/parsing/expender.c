/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:34:06 by mkane             #+#    #+#             */
/*   Updated: 2024/04/30 20:05:50 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	find_pipe(t_minishell *minishell);
static int	find_builtins(t_minishell *minishell);

static int	init_cmds(t_minishell *minishell)
{
	t_token	*token;
	t_cmd	*new;

	token = minishell->token;
	while (token)
	{
		if (token->type == COMMAND)
		{
			new = cmd_lstnew(token->cmd);
			if (!new)
				return (0);
			cmd_lstadd_back(&minishell->cmd, new);
		}
		token = token->next;
	}
	if (!minishell->cmd)
		return (0);
	return (1);
}

void	expender(t_minishell *minishell)
{

	// if nbcmd == 1 && cmd == BUILTIN {}
	// function exec builtin
	//  redirection
		// exec builtin
		// return
	// else
	/*
		while (i < nbcmd)
		{
			pipe(fd)
			pid[i] = fork()
			if (pid == 0)
			{
				redirection pipe
				redirection file
				execve
			}
			else
			{
				le bail de pipe
			}
		}

		while (i < nbcmd)
			waitppid(pid[i], &status, 0)
			if (WIFEXITED(status))
				minishell->status = WEXITSTATUS(status);
			
	*/

	int status;

	if (find_pipe(minishell))
		return (minishell_pipe(minishell));
	if (!redirection(minishell))
		return ;
	if (!init_files(minishell))
		return (free_and_close(minishell));
	if (!init_cmds(minishell))
		return (free_and_close(minishell));
	if (find_builtins(minishell) == ECHO)
		return (echo(minishell));
	if (find_builtins(minishell) == CD)
		return (cd(minishell));
	if (find_builtins(minishell) == PWD)
		return (pwd(minishell));
	if (find_builtins(minishell) == EXPORT)
		return (export(minishell));
	if (find_builtins(minishell) == UNSET)
		return (unset(minishell));
	if (find_builtins(minishell) == ENV)
		return (env(minishell));
	if (find_builtins(minishell) == EXIT)
		return (exit_minishell(minishell));
	waitpid(minishell_execve(minishell), &status, 0);
	if (WIFEXITED(status))
        minishell->status = WEXITSTATUS(status);
}


static int	find_pipe(t_minishell *minishell)
{
	t_token	*token;

	token = minishell->token;
	while (token)
	{
		if (token->type == PIPE)
			return (1);
		token = token->next;
	}
	return (0);
}

static int	find_builtins(t_minishell *minishell)
{
	t_token	*token;

	token = minishell->token;
	while (token)
	{
		if (token->type == COMMAND)
		{
			if (ft_strcmp(token->cmd, "echo") == 0)
				return (minishell->builtin = ECHO);
			if (ft_strcmp(token->cmd, "cd") == 0)
				return (minishell->builtin = CD);
			if (ft_strcmp(token->cmd, "pwd") == 0)
				return (minishell->builtin = PWD);
			if (ft_strcmp(token->cmd, "export") == 0)
				return (minishell->builtin = EXPORT);
			if (ft_strcmp(token->cmd, "unset") == 0)
				return (minishell->builtin = UNSET);
			if (ft_strcmp(token->cmd, "env") == 0)
				return (minishell->builtin = ENV);
			if (ft_strcmp(token->cmd, "exit") == 0)
				return (minishell->builtin = EXIT);
		}
		token = token->next;
	}
	return (minishell->builtin = -1);
}
