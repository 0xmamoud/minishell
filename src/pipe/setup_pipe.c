/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 22:51:42 by mkane             #+#    #+#             */
/*   Updated: 2024/05/13 21:40:29 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pipe_update_index(t_minishell *minishell);
static void	pipe_nullify(t_minishell *minishell, t_pipe_cmds **pipe);

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
		pipe_nullify(minishell, &pipe);
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

void	pipe_open_heredocs(t_minishell *minishell)
{
	t_pipe_cmds	*cmds;

	cmds = minishell->pipe.cmds;
	while (cmds)
	{
		if (cmds->in.type == HEREDOC)
		{
			ft_here_doc(&cmds->in.file, minishell);
		}
		if (get_status(0, 3) == 130)
			return ;
		cmds = cmds->next;
	}
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

static void	pipe_nullify(t_minishell *minishell, t_pipe_cmds **pipe)
{
		(*pipe)->in.fd = -1;
		(*pipe)->out.fd = -1;
		(*pipe)->in.file = NULL;
		(*pipe)->out.file = NULL;
		(*pipe)->in.type = -1;
		(*pipe)->out.type = -1;
		minishell->in.fd = -1;
		minishell->out.fd = -1;
		minishell->in.file = NULL;
		minishell->out.file = NULL;
		minishell->in.type = -1;
		minishell->out.type = -1;
		minishell->in.saved_stdin = -1;
		minishell->out.saved_stdout = -1;
}
