/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:18:26 by tbarret           #+#    #+#             */
/*   Updated: 2024/05/03 00:14:02 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	ft_here_doc(char **delimiter, t_minishell *minishell)
{
	pid_t	pid;
	int		status;
	char	*line;

	char *(fd_name) = ft_join("here_doc.", *delimiter);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		signal(SIGINT, control_c_heredoc);
		int (fd) = open(fd_name, O_CREAT | O_RDWR | O_TRUNC, 0777);
		line = NULL;
		if (fd < 0)
			return ;
		while (1)
		{
			line = readline("> ");
			if (!line)
				break ;
			if (ft_strcmp(line, *delimiter) == 0 || line[0] == EOF)
			{
				free(line);
				break ;
			}
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			free(line);
		}
		close(fd);
		free(*delimiter);
		*delimiter = fd_name;
		env_lstclear(&minishell->env);
		pipe_lstclear(&minishell->pipe.cmds);
		cmd_lstclear(&minishell->cmd);
		pipe_lstclear(&minishell->pipe.cmds);
		token_lstclear(&minishell->token);
		free(minishell->line);
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
		exit(0);

	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		get_status(WEXITSTATUS(status), 0);
	free(*delimiter);
	*delimiter = NULL;
	*delimiter = ft_strdup(fd_name);
	free(fd_name);
	signal(SIGINT, control_c_parent);
	signal(SIGQUIT, SIG_IGN);
}
