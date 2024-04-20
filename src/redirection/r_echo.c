/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:23:36 by mkane             #+#    #+#             */
/*   Updated: 2024/04/20 21:49:06 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	infile(t_minishell *minishell);
static int	outfile(t_minishell *minishell);

int	echo_redirection(t_minishell *minishell)
{
	minishell->echo.in.type = -1;
	minishell->echo.out.type = -1;
	if (!infile(minishell))
		return (0);
	if (!outfile(minishell))
	{
		free(minishell->echo.in.file);
		return (0);
	}
	return (1);
}

static int	infile(t_minishell *minishell)
{
	t_token	*token;

	token = minishell->token;
	while (token && token->type != COMMAND)
	{
		if (token->type == REDIRECTION)
		{
			if (token->cmd[0] == '<' && token->cmd[1] != '<')
				return (infile_case(minishell, token->cmd));
			if (token->cmd[0] == '<' && token->cmd[1] == '<')
				return (heredoc_case(minishell, token->cmd));
		}
		token = token->next;
	}
	return (1);
}

static int	outfile(t_minishell *minishell)
{
	t_token	*token;

	token = minishell->token;
	while (token && token->type != COMMAND)
		token = token->next;
	if (token)
		token = token->next;
	if (token && token->type == COMMAND && ft_strncmp(token->cmd, "-n",
			ft_strlen(token->cmd)) == 0)
		token = token->next;
	while (token && token->type != COMMAND)
	{
		if (token->type == REDIRECTION)
		{
			if (token->cmd[0] == '>' && token->cmd[1] != '>')
				return (outfile_case(minishell, token->cmd));
			if (token->cmd[0] == '>' && token->cmd[1] == '>')
				return (outfile_append_case(minishell, token->cmd));
		}
		token = token->next;
	}
	return (1);
}
