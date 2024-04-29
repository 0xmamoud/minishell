/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:49:23 by mkane             #+#    #+#             */
/*   Updated: 2024/04/27 18:15:09 by tbarret          ###   ########.fr       */
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
	if ((int)minishell->in.type != -1 && init_input(minishell) == 0)
		return (0);
	if ((int)minishell->out.type != -1 && init_output(minishell) == 0)
		return (0);
	return (1);
}

static int	init_input(t_minishell *minishell)
{
	minishell->in.saved_stdin = dup(STDIN_FILENO);
	if (minishell->in.type == REDIR_IN)
		minishell->in.fd = open(minishell->in.file, O_RDONLY);
	else if (minishell->in.type == HEREDOC)
	{
		ft_here_doc(&minishell->in.file);
		minishell->in.fd = open(minishell->in.file, O_RDONLY);
		if (minishell->in.fd == -1)
		{
			ft_putstr_fd("No such file or directory\n", 2);
			return (ft_exit(1, 0, 0));
		
		}
	}
	if (minishell->in.fd == -1)
	{
		ft_putstr_fd("No such file or directory\n", 2);
		return (ft_exit(1, 0, 0));
	}
	if (dup2(minishell->in.fd, STDIN_FILENO) < 0)
		return (0);
	return (1);
}

static int	init_output(t_minishell *minishell)
{
	minishell->out.saved_stdout = dup(STDOUT_FILENO);
	if (minishell->out.type == REDIR_OUT)
		minishell->out.fd = open(minishell->out.file,
				O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (minishell->out.type == REDIR_OUT_APPEND)
		minishell->out.fd = open(minishell->out.file,
				O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (minishell->out.fd == -1)
	{
		ft_putstr_fd(": No such file or directory\n", 2);
		return (ft_exit(1, 0, 0));
	}
	if (dup2(minishell->out.fd, STDOUT_FILENO) < 0)
		return (0);
	return (1);
}
