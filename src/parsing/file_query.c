/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_query.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:58:35 by tbarret           #+#    #+#             */
/*   Updated: 2024/04/29 22:31:54 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_file(t_minishell *minishell, char *file,
				t_type_redirection type);

int	handle_files(t_minishell *minishell)
{
	t_token *(token) = minishell->token;
	int (i) = 1;
	while (token)
	{
		if (token->type == REDIRECTION)
		{
			if (token->cmd[0] == '<' && token->cmd[1] != '<')
				i = get_file(minishell, token->cmd, REDIR_IN);
			if (token->cmd[0] == '<' && token->cmd[1] == '<')
				i = get_file(minishell, token->cmd, HEREDOC);
			if (token->cmd[0] == '>' && token->cmd[1] != '>')
				i = get_file(minishell, token->cmd, REDIR_OUT);
			if (token->cmd[0] == '>' && token->cmd[1] == '>')
				i = get_file(minishell, token->cmd, REDIR_OUT_APPEND);
			if (!i)
				return (0);
		}
		token = token->next;
	}
	return (1);
}

void	free_and_close(t_minishell *minishell)
{
	if (minishell->in.fd != -1)
	{
		dup2(minishell->in.saved_stdin, STDIN_FILENO);
		close(minishell->in.saved_stdin);
		close(minishell->in.fd);
		if (minishell->in.type == HEREDOC)
			unlink(minishell->in.file);
	}
	if (minishell->out.fd != -1)
	{
		dup2(minishell->out.saved_stdout, STDOUT_FILENO);
		close(minishell->out.saved_stdout);
		close(minishell->out.fd);
	}
	if ((int)minishell->in.type != -1)
		free(minishell->in.file);
	if ((int)minishell->out.type != -1)
		free(minishell->out.file);
}

static int	get_file(t_minishell *minishell, char *file,
		t_type_redirection type)
{
	int	i;

	i = 1;
	while (file[i] && (file[i] == ' ' || file[i] == '>' || file[i] == '<'))
		i++;
	if (type == REDIR_IN || type == HEREDOC)
	{
		if (minishell->in.file)
			free(minishell->in.file);
		minishell->in.file = strdup(&file[i]);
		if (!minishell->in.file)
			return (0);
		minishell->in.type = type;
	}
	else
	{
		if (minishell->out.file)
			free(minishell->out.file);
		minishell->out.file = strdup(&file[i]);
		if (!minishell->out.file)
			return (0);
		minishell->out.type = type;
	}
	return (1);
}
