/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:34:06 by mkane             #+#    #+#             */
/*   Updated: 2024/04/26 23:49:28 by mkane            ###   ########.fr       */
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
	return (1);
}

void	expender(t_minishell *minishell)
{
	if (find_pipe(minishell))
	{
		printf("pipe\n");
		return ;
	}
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
	free_and_close(minishell);
	minishell_execve(minishell);
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
