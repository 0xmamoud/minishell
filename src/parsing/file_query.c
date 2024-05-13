/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_query.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:58:35 by tbarret           #+#    #+#             */
/*   Updated: 2024/05/13 17:25:13 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_file(t_minishell *minishell, char *file,
				t_type_redirection type);
static int	handle_infile(t_minishell *minishell, char *file,
				t_type_redirection type);
static int	handle_outfile(t_minishell *minishell, char *file,
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

static int	get_file(t_minishell *minishell, char *file,
		t_type_redirection type)
{
	int	i;

	i = 1;
	while (file[i] && (file[i] == ' ' || file[i] == '>' || file[i] == '<'))
		i++;
	if (type == REDIR_IN || type == HEREDOC)
	{
		if (!handle_infile(minishell, &file[i], type))
			return (0);
	}
	else if (type == REDIR_OUT || type == REDIR_OUT_APPEND)
	{
		if (!handle_outfile(minishell, &file[i], type))
			return (0);
	}
	return (1);
}

static int	handle_infile(t_minishell *minishell, char *file,
	t_type_redirection type)
{
	if (minishell->in.file)
	{
		free(minishell->in.file);
		minishell->in.file = NULL;
	}
	minishell->in.file = strdup(file);
	if (!minishell->in.file)
		return (0);
	minishell->in.type = type;
	if (ft_strcmp(file, "") == 0 || ft_strcmp(file, " ") == 0
		|| ft_strcmp(file, "*") == 0)
		return (ft_exit(1, 0, 0));
	if (type == REDIR_IN)
	{
		if (access(file, F_OK) == -1)
		{
			perror(file);
			return (ft_exit(1, 0, 0));
		}
	}
	return (1);
}

static int	handle_outfile(t_minishell *minishell, char *file,
	t_type_redirection type)
{
	int	fd;

	if (minishell->out.file)
	{
		free(minishell->out.file);
		minishell->out.file = NULL;
	}
	if (ft_strcmp(file, "") == 0 || ft_strcmp(file, " ") == 0
		|| ft_strcmp(file, "*") == 0)
		return (ft_exit(1, 0, 0));
	minishell->out.file = strdup(file);
	if (!minishell->out.file)
		return (0);
	minishell->out.type = type;
	if (type == REDIR_OUT)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
	{
		perror(file);
		return (ft_exit(1, 0, 0));
	}
	close(fd);
	return (1);
}

void	free_and_close(t_minishell *minishell)
{
	if (minishell->in.file || (int)minishell->in.type != -1)
	{
		if (minishell->in.saved_stdin != -1)
		{
			dup2(minishell->in.saved_stdin, STDIN_FILENO);
			close(minishell->in.saved_stdin);
		}
		if (minishell->in.type == HEREDOC)
			unlink(minishell->in.file);
		if (minishell->in.file)
			free(minishell->in.file);
	}
	if (minishell->out.file || (int)minishell->out.type != -1)
	{
		if (minishell->out.saved_stdout != -1)
		{
			dup2(minishell->out.saved_stdout, STDOUT_FILENO);
			close(minishell->out.saved_stdout);
		}
		if (minishell->out.file)
			free(minishell->out.file);
	}
}
