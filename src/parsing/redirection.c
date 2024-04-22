/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:49:23 by mkane             #+#    #+#             */
/*   Updated: 2024/04/22 16:32:08 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_files(t_minishell *minishell);
static int	get_file(t_minishell *minishell, char *file,
				t_type_redirection type);

int	redirection(t_minishell *minishell)
{
	minishell->echo.option = 0;
	minishell->out.saved_stdout = -1;
	minishell->in.fd = -1;
	minishell->out.fd = -1;
	minishell->in.type = -1;
	minishell->out.type = -1;
	minishell->in.file = NULL;
	minishell->out.file = NULL;
	if (!handle_files(minishell))
	{
		if (minishell->in.file)
			free(minishell->in.file);
		if (minishell->out.file)
			free(minishell->out.file);
		return (0);
	}
	return (1);
}

int	init_files(t_minishell *minishell)
{
	if ((int)minishell->in.type != -1)
	{
		if (minishell->in.type == REDIR_IN)
			minishell->in.fd = open(minishell->in.file, O_RDONLY);
		if (minishell->in.type == HEREDOC)
			minishell->in.fd = open(minishell->in.file, O_RDONLY);
		if (minishell->in.fd == -1)
			return (ft_putstr_fd(": No such file or directory\n", 2), 0);
	}
	if ((int)minishell->out.type != -1)
	{
		minishell->out.saved_stdout = dup(STDOUT_FILENO);
		if (minishell->out.type == REDIR_OUT)
			minishell->out.fd = open(minishell->out.file,
					O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (minishell->out.type == REDIR_OUT_APPEND)
			minishell->out.fd = open(minishell->out.file,
					O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (minishell->out.fd == -1)
			return (ft_putstr_fd(": No such file or directory\n", 2), 0);
		if (dup2(minishell->out.fd, STDOUT_FILENO) < 0)
			return (0);
	}
	return (1);
}

void	free_and_close(t_minishell *minishell)
{
	if (minishell->in.fd != -1)
		close(minishell->in.fd);
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

static int	handle_files(t_minishell *minishell)
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
	if (file[i] == ' ')
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
