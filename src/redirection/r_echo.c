/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:23:36 by mkane             #+#    #+#             */
/*   Updated: 2024/04/21 23:05:19 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	infile(t_minishell *minishell);
static int	outfile(t_minishell *minishell);

int	echo_redirection(t_minishell *minishell)
{
	minishell->echo.option = 0;
	minishell->echo.out.saved_stdout = -1;
	minishell->echo.in.fd = -1;
	minishell->echo.out.fd = -1;
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

int	init_files(t_minishell *minishell)
{
	if ((int)minishell->echo.in.type != -1)
	{
		if (minishell->echo.in.type == REDIR_IN)
			minishell->echo.in.fd = open(minishell->echo.in.file, O_RDONLY);
		if (minishell->echo.in.type == HEREDOC)
			minishell->echo.in.fd = open(minishell->echo.in.file, O_RDONLY);
		if (minishell->echo.in.fd == -1)
			return (ft_putstr_fd(": No such file or directory\n", 2), 0);
	}
	if ((int)minishell->echo.out.type != -1)
	{
		minishell->echo.out.saved_stdout = dup(STDOUT_FILENO);
		if (minishell->echo.out.type == REDIR_OUT)
			minishell->echo.out.fd = open(minishell->echo.out.file,
					O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (minishell->echo.out.type == REDIR_OUT_APPEND)
			minishell->echo.out.fd = open(minishell->echo.out.file,
					O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (minishell->echo.out.fd == -1)
			return (ft_putstr_fd(": No such file or directory\n", 2), 0);
		if (dup2(minishell->echo.out.fd, STDOUT_FILENO) < 0)
			return (0);
	}
	return (1);
}

static int	infile(t_minishell *minishell)
{
	t_token	*token;

	token = minishell->token;
	while (token)
	{
		if (token->type == REDIRECTION)
		{
			if (token->cmd[0] == '<' && token->cmd[1] != '<')
			{
				if (!infile_case(minishell, token->cmd))
					return (0);
			}
			if (token->cmd[0] == '<' && token->cmd[1] == '<')
			{
				if (!heredoc_case(minishell, token->cmd))
					return (0);
			}
		}
		token = token->next;
	}
	return (1);
}

static int	outfile(t_minishell *minishell)
{
	t_token	*token;

	token = minishell->token;
	while (token)
	{
		if (token->type == REDIRECTION)
		{
			if (token->cmd[0] == '>' && token->cmd[1] != '>')
			{
				if (!outfile_case(minishell, token->cmd))
					return (0);
			}
			if (token->cmd[0] == '>' && token->cmd[1] == '>')
			{
				if (!outfile_append_case(minishell, token->cmd))
					return (0);
			}
		}
		token = token->next;
	}
	return (1);
}
