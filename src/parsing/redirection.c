/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:49:23 by mkane             #+#    #+#             */
/*   Updated: 2024/05/13 21:36:25 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	init_input(t_minishell *minishell);
static int	init_output(t_minishell *minishell);

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
	if (minishell->in.file)
	{
		if (!init_input(minishell))
			return (0);
	}
	if (minishell->out.file)
	{
		if (!init_output(minishell))
			return (0);
	}
	if (get_status(0, 3) == 130)
		return (0);
	return (1);
}

static int	init_input(t_minishell *minishell)
{
	if (minishell->in.type == HEREDOC)
		ft_here_doc(&minishell->in.file, minishell);
	minishell->in.fd = open(minishell->in.file, O_RDONLY);
	if (minishell->in.fd == -1)
	{
		perror(minishell->in.file);
		ft_exit(errno, 0, 0);
		if (minishell->in.type == HEREDOC)
			unlink(minishell->in.file);
		return (0);
	}
	minishell->in.saved_stdin = dup(STDIN_FILENO);
	if (dup2(minishell->in.fd, STDIN_FILENO) < 0)
	{
		perror(minishell->in.file);
		return (ft_exit(errno, 0, 0));
	}
	close(minishell->in.fd);
	return (1);
}

static int	init_output(t_minishell *minishell)
{
	if (minishell->out.type == REDIR_OUT)
		minishell->out.fd = open(minishell->out.file,
				O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		minishell->out.fd = open(minishell->out.file,
				O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (minishell->out.fd == -1)
	{
		perror(minishell->out.file);
		ft_exit(errno, 0, 0);
		if (minishell->in.file && minishell->in.type == HEREDOC)
			unlink(minishell->in.file);
		return (0);
	}
	minishell->out.saved_stdout = dup(STDOUT_FILENO);
	if (dup2(minishell->out.fd, STDOUT_FILENO) < 0)
	{
		perror(minishell->out.file);
		return (ft_exit(errno, 0, 0));
	}
	close(minishell->out.fd);
	return (1);
}
