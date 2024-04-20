/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:34:06 by mkane             #+#    #+#             */
/*   Updated: 2024/04/20 21:25:37 by mkane            ###   ########.fr       */
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
	{
		echo(minishell);
		return ;
	}
	if (find_builtins(minishell) == CD)
	{
		printf("cd\n");
		return ;
	}
	if (find_builtins(minishell) == PWD)
	{
		printf("pwd\n");
		return ;
	}
	if (find_builtins(minishell) == EXPORT)
	{
		printf("export\n");
		return ;
	}
	if (find_builtins(minishell) == UNSET)
	{
		printf("unset\n");
		return ;
	}
	if (find_builtins(minishell) == ENV)
	{
		printf("env\n");
		return ;
	}
	if (find_builtins(minishell) == EXIT)
	{
		printf("exit\n");
		return ;
	}
	printf("exec\n");
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