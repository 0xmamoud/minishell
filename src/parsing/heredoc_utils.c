/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:30:58 by tbarret           #+#    #+#             */
/*   Updated: 2024/05/13 17:50:26 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clear_heredoc_pipe(t_pipe_cmds **pipe)
{
	t_pipe_cmds	*tmp;

	while (*pipe)
	{
		if ((*pipe)->in.file)
			free((*pipe)->in.file);
		if ((*pipe)->out.file)
			free((*pipe)->out.file);
		tmp = *pipe;
		*pipe = (*pipe)->next;
		free(tmp->cmd);
		free(tmp);
	}
}

void	ft_heredoc_exit_free_minishell(t_minishell *minishell)
{
	env_lstclear(&minishell->env);
	clear_heredoc_pipe(&minishell->pipe.cmds);
	cmd_lstclear(&minishell->cmd);
	token_lstclear(&minishell->token);
	free(minishell->line);
	rl_clear_history();
}

void	ft_heredoc_clear_file(t_minishell *minishell)
{
	if (minishell->in.saved_stdin != -1)
		close(minishell->in.saved_stdin);
	if (minishell->out.saved_stdout != -1)
		close(minishell->out.saved_stdout);
	if (minishell->in.fd != -1)
		close(minishell->in.fd);
	if (minishell->out.fd != -1)
		close(minishell->out.fd);
	free(minishell->in.file);
	if (minishell->out.file)
		free(minishell->out.file);
	exit(get_status(0, 3));
}

int	ft_open_heredoc_fd(char **delimiter, char *fd_name)
{
	int	fd;

	fd = open(fd_name, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd == -1)
	{
		free(*delimiter);
		*delimiter = NULL;
		*delimiter = ft_strdup(fd_name);
		free(fd_name);
		return (-1);
	}
	return (fd);
}
