/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:18:26 by tbarret           #+#    #+#             */
/*   Updated: 2024/05/13 17:50:17 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_read(char **delimiter, int fd)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = get_next_line(0, 0);
		if (!line)
			break ;
		if (ft_strcmp(line, *delimiter) == 0 || line[0] == EOF)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	get_next_line(0, 1);
	close(fd);
}

static void	heredoc_exec(t_minishell *minishell, int fd, char *fd_name,
		char **delimiter)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		minishell->in.saved_stdin = -1;
		minishell->out.saved_stdout = -1;
		signal(SIGINT, control_c_heredoc);
		ft_read(delimiter, fd);
		free(*delimiter);
		*delimiter = fd_name;
		ft_heredoc_exit_free_minishell(minishell);
		ft_heredoc_clear_file(minishell);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		get_status(WEXITSTATUS(status), 0);
	free(*delimiter);
	close(fd);
	*delimiter = NULL;
	*delimiter = ft_strdup(fd_name);
	free(fd_name);
}

void	ft_here_doc(char **delimiter, t_minishell *minishell)
{
	char	*tmp;

	char *(fd_name) = ft_join("here_doc.", *delimiter);
	if (!fd_name)
		return ;
	tmp = ft_strjoin(*delimiter, "\n");
	if (!tmp)
	{
		free(fd_name);
		return ;
	}
	*delimiter = tmp;
	int (fd) = ft_open_heredoc_fd(delimiter, fd_name);
	signal(SIGINT, SIG_IGN);
	heredoc_exec(minishell, fd, fd_name, delimiter);
	signal(SIGINT, control_c_parent);
	signal(SIGQUIT, SIG_IGN);
}
