/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:18:26 by tbarret           #+#    #+#             */
/*   Updated: 2024/05/02 20:53:18 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	ft_here_doc(char **delimiter, t_minishell *minishell)
{
	pid_t	pid;
	int		status;
	char	*line;

	(void)minishell;
	char *(fd_name) = ft_strjoin(ft_strdup("here_doc."), *delimiter);
	pid = fork();
	if (pid < 0)
		return ;
	signal(SIGINT, control_c_child);
	signal(SIGQUIT, control_back_slash_child);
	if (pid == 0)
	{
		int (fd) = open(fd_name, O_CREAT | O_RDWR | O_TRUNC, 0777);
		line = NULL;
		if (fd < 0)
			return ;
		while (1)
		{
			line = readline("> ");
			if (get_status(0, 3) == 130)
			{
				free(line);
				break ;
			}
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
		// free(*delimiter);
		// *delimiter = fd_name;
		// env_lstclear(&minishell->env);
		// pipe_lstclear(&minishell->pipe.cmds);
		// cmd_lstclear(&minishell->cmd);
		// token_lstclear(&minishell->token);
		// free(minishell->line);
		// if (minishell->pipe.pid)
		// 	free(minishell->pipe.pid);
		// if (minishell->in.saved_stdin != -1)
		// 	close(minishell->in.saved_stdin);
		// if (minishell->out.saved_stdout != -1)
		// 	close(minishell->out.saved_stdout);
		// if (minishell->in.fd != -1)
		// 	close(minishell->in.fd);
		// if (minishell->out.fd != -1)
		// 	close(minishell->out.fd);
		// if (minishell->pipe.prev_fd != -1)
		// 	close(minishell->pipe.prev_fd);
		// if (minishell->in.file)
		// 	free(minishell->in.file);
		// if (minishell->out.file)
		// 	free(minishell->out.file);
		exit(0);

	}
	signal(SIGINT, control_c_parent);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		get_status(WEXITSTATUS(status), 0);
	free(*delimiter);
	*delimiter = fd_name;
}
