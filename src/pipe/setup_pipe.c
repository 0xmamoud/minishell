/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 22:51:42 by mkane             #+#    #+#             */
/*   Updated: 2024/05/08 20:48:26 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	sub_pipe_redirection(t_token *token, t_pipe_cmds **pipe);
static int	get_file_infos(char *filename, t_pipe_cmds **pipe,
				t_type_redirection type);
static void	pipe_update_index(t_minishell *minishell);

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
	pipe_update_index(minishell);
	free(cmd);
	return (1);
}

int	pipe_redirection(t_minishell *minishell)
{
	t_token *(token) = minishell->token;
	t_pipe_cmds *(pipe) = minishell->pipe.cmds;

	while (pipe)
	{
		pipe->in.fd = -1;
		pipe->out.fd = -1;
		pipe->in.file = NULL;
		pipe->out.file = NULL;
		pipe->in.type = -1;
		pipe->out.type = -1;
		minishell->in.fd = -1;
		minishell->out.fd = -1;
		minishell->in.file = NULL;
		minishell->out.file = NULL;
		minishell->in.type = -1;
		minishell->out.type = -1;
		minishell->in.saved_stdin = -1;
		minishell->out.saved_stdout = -1;
		while (token && token->type != PIPE)
		{
			if (token->type == REDIRECTION)
			{
				if (!sub_pipe_redirection(token, &pipe))
				{
					while (token && token->next && token->next->type != PIPE)
						token = token->next;
				}
			}
			if (token)
				token = token->next;
		}
		if (token && token->type == PIPE)
			token = token->next;
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
	int	fd;
	int (i) = 1;
	while (filename[i] == ' ' || filename[i] == '>' || filename[i] == '<')
		i++;
	if (type == REDIR_IN || type == HEREDOC)
	{
		if ((*pipe)->in.file)
		{
			free((*pipe)->in.file);
			(*pipe)->in.file = NULL;
		}
		(*pipe)->in.type = type;
		(*pipe)->in.file = ft_strdup(&filename[i]);
		if (!(*pipe)->in.file)
			return (0);
		if (type == REDIR_IN)
		{
			if (access(&filename[i], F_OK) == -1)
				return (0);
		}
	}
	else if (type == REDIR_OUT || type == REDIR_OUT_APPEND)
	{
		if ((*pipe)->out.file)
		{
			free((*pipe)->out.file);
			(*pipe)->out.file = NULL;
		}
		(*pipe)->out.type = type;
		(*pipe)->out.file = ft_strdup(&filename[i]);
		if (!(*pipe)->out.file)
			return (0);
		if (type == REDIR_OUT)
			fd = open(&filename[i], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		else
			fd = open(&filename[i], O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (fd == -1)
			return (0);
		close(fd);
	}
	return (1);
}

static void	pipe_update_index(t_minishell *minishell)
{
	t_pipe_cmds	*cmds;
	int			index;

	cmds = minishell->pipe.cmds;
	index = 0;
	while (cmds)
	{
		cmds->index = index;
		index++;
		cmds = cmds->next;
	}
}
