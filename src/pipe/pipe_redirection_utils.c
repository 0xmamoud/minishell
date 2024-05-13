/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redirection_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 20:25:14 by mkane             #+#    #+#             */
/*   Updated: 2024/05/13 21:40:49 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_file_infos(char *filename, t_pipe_cmds **pipe,
				t_type_redirection type);
static int	infile_infos(char *filename, t_type_redirection type,
				t_pipe_cmds **pipe);
static int	outfile_infos(char *filename, t_type_redirection type,
				t_pipe_cmds **pipe);

int	sub_pipe_redirection(t_token *token, t_pipe_cmds **pipe)
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
		if (!infile_infos(&filename[i], type, pipe))
			return (0);
	}
	else if (type == REDIR_OUT || type == REDIR_OUT_APPEND)
	{
		if (!outfile_infos(&filename[i], type, pipe))
			return (0);
	}
	return (1);
}

static	int	infile_infos(char *filename, t_type_redirection type,
	t_pipe_cmds **pipe)
{
	if ((*pipe)->in.file)
	{
		free((*pipe)->in.file);
		(*pipe)->in.file = NULL;
	}
	(*pipe)->in.type = type;
	(*pipe)->in.file = ft_strdup(filename);
	if (!(*pipe)->in.file)
		return (0);
	if (type == REDIR_IN)
	{
		if (access(filename, F_OK) == -1)
			return (0);
	}
	return (1);
}

static int	outfile_infos(char *filename, t_type_redirection type,
	t_pipe_cmds **pipe)
{
	int	fd;

	if ((*pipe)->out.file)
	{
		free((*pipe)->out.file);
		(*pipe)->out.file = NULL;
	}
	(*pipe)->out.type = type;
	(*pipe)->out.file = ft_strdup(filename);
	if (!(*pipe)->out.file)
		return (0);
	if (type == REDIR_OUT)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}
