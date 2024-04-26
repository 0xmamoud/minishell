/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:34:06 by mkane             #+#    #+#             */
/*   Updated: 2024/04/26 17:05:58 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	find_pipe(t_minishell *minishell);
static int	find_builtins(t_minishell *minishell);

void	expender(t_minishell *minishell)
{
	if (find_pipe(minishell))
	{
		printf("pipe\n");
		return ;
	}
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
			if (ft_strncmp(token->cmd, "echo", 4) == 0)
				return (minishell->builtin = ECHO);
			if (ft_strncmp(token->cmd, "cd", 2) == 0)
				return (minishell->builtin = CD);
			if (ft_strncmp(token->cmd, "pwd", 3) == 0)
				return (minishell->builtin = PWD);
			if (ft_strncmp(token->cmd, "export", 6) == 0)
				return (minishell->builtin = EXPORT);
			if (ft_strncmp(token->cmd, "unset", 5) == 0)
				return (minishell->builtin = UNSET);
			if (ft_strncmp(token->cmd, "env", 3) == 0)
				return (minishell->builtin = ENV);
			if (ft_strncmp(token->cmd, "exit", 4) == 0)
				return (minishell->builtin = EXIT);
		}
		token = token->next;
	}
	return (minishell->builtin = -1);
}
