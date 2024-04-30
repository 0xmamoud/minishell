/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 22:51:42 by mkane             #+#    #+#             */
/*   Updated: 2024/04/30 19:11:01 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	sub_pipe_redirection(t_token *token, t_pipe_cmds **pipe);
static int	get_file_infos(char *filename, t_pipe_cmds **pipe,
				t_type_redirection type);

int	init_pipe(t_minishell *minishell)
{
	char *(cmd) = ft_strdup("");
	t_token *(token) = minishell->token;
	while (token)
	{
		while (token && token->type != PIPE)
		{
			if (token->type == COMMAND)
			{
				cmd = ft_strjoin(cmd, token->cmd);
				if (!cmd)
					return (0);
				cmd = ft_strjoin(cmd, " ");
			}
			token = token->next;
		}
		pipe_lstadd_back(&minishell->pipe.cmds, pipe_lstnew(cmd, 0));
		free(cmd);
		cmd = ft_strdup("");
		if (token)
			token = token->next;
	}
	free(cmd);
	return (1);
}

int	pipe_redirection(t_minishell *minishell)
{
	t_token *(token) = minishell->token;
	t_pipe_cmds *(pipe) = minishell->pipe.cmds;

	while (pipe)
	{
		if (token && token->type == PIPE)
			token = token->next;
		while (token && token->type != PIPE)
		{
			if (token->type == REDIRECTION)
			{
				if (!sub_pipe_redirection(token, &pipe))
					return (0);
			}
			token = token->next;
		}
		pipe = pipe->next;
	}
	return (1);
}

static int	sub_pipe_redirection(t_token *token, t_pipe_cmds **pipe)
{

	if (token->cmd[0] == '<' && token->cmd[1] != '<')
	{
		if (!get_file_infos(token->cmd, pipe, REDIR_IN))
			return (0);
	}
	if (token->cmd[0] == '<' && token->cmd[1] == '<')
	{
		if (!get_file_infos(token->cmd, pipe, HEREDOC))
			return (0);
	}
	if (token->cmd[0] == '>' && token->cmd[1] != '>')
	{
		if (!get_file_infos(token->cmd, pipe, REDIR_OUT))
			return (0);
	}
	if (token->cmd[0] == '>' && token->cmd[1] == '>')
	{
		if (!get_file_infos(token->cmd, pipe, REDIR_OUT_APPEND))
			return (0);
	}
	return (1);
}

static int	get_file_infos(char *filename, t_pipe_cmds **pipe,
		t_type_redirection type)
{
	int (i) = 1;
	while (filename[i] == ' ' || filename[i] == '>' || filename[i] == '<')
		i++;
	if (type == REDIR_IN || type == HEREDOC)
	{
		if ((*pipe)->in.file)
			free((*pipe)->in.file);
		(*pipe)->in.file = ft_strdup(&filename[i]);
		if (!(*pipe)->in.file)
			return (0);
		(*pipe)->in.type = type;
	}
	else if (type == REDIR_OUT || type == REDIR_OUT_APPEND)
	{
		if ((*pipe)->out.file)
			free((*pipe)->out.file);
		(*pipe)->out.file = ft_strdup(&filename[i]);
		if (!(*pipe)->out.file)
			return (0);
		(*pipe)->out.type = type;
	}
	return (1);
}
