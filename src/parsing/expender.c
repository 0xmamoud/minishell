/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:34:06 by mkane             #+#    #+#             */
/*   Updated: 2024/05/10 23:22:06 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	find_pipe(t_minishell *minishell);
static int	find_builtins(t_minishell *minishell);
static int	init_cmds(t_minishell *minishell);
static void	bultins_manager(t_minishell *minishell);

void	expender(t_minishell *minishell)
{
	get_status(0, 0);
	if (find_pipe(minishell))
		return (minishell_pipe(minishell));
	if (!redirection(minishell))
		return ;
	if (!init_files(minishell))
		return (free_and_close(minishell));
	if (!init_cmds(minishell))
		return (free_and_close(minishell));
	bultins_manager(minishell);
	free_and_close(minishell);
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

static void	bultins_manager(t_minishell *minishell)
{
	find_builtins(minishell);
	if (minishell->builtin == ECHO)
		echo(minishell);
	else if (minishell->builtin == CD)
		cd(minishell);
	else if (minishell->builtin == PWD)
		pwd();
	else if (minishell->builtin == EXPORT)
		export(minishell);
	else if (minishell->builtin == UNSET)
		unset(minishell);
	else if (minishell->builtin == ENV)
		env(minishell);
	else if (minishell->builtin == EXIT)
		exit_minishell(minishell);
	else
		minishell_execve(minishell);
}

static int	find_builtins(t_minishell *minishell)
{
	t_token	*token;

	token = minishell->token;
	while (token && token->type != COMMAND)
		token = token->next;
	if (!token)
		return (minishell->builtin = BUILTIN_COUNT);
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
	return (minishell->builtin = BUILTIN_COUNT);
}
