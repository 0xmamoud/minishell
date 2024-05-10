/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:18:26 by tbarret           #+#    #+#             */
/*   Updated: 2024/05/10 17:53:21 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static int 	after_dollars(char a)
{
	if (a == '\'' || a == '\"' || a == ' ' || a == '\n' || !a)
		return (0);
	return (1);
}

static void var_doc(t_minishell *minishell, char *line, int fd)
{
	int i;
	int j;
	char c;
	char *tmp;

	i = 0;
	j = 0;
	tmp = NULL;
	while(line[i])
	{
		// if (line[i] == '$' && line[i + 1] == '\n')
		// {
		// 	ft_putstr_fd(&line[i], fd);
		// 	break ;
		// }
		if (line[i] == '$' && after_dollars(line[i + 1]))
		{
	
			// if (!line[i + 1] || (line[i + 1] && line[i + 1] == ' ')) 
			// {
			// 	write(fd, &line[i], 1);
			// 	i++;
			// 	continue ;
			// }
			i++;
			j = i;
			while ((ft_isalpha(line[j]) || line[j] == '_' || line[j] == '?'))
				j++;
			c = line[j];
			line[j] = '\0';
			if (line[i] == '?')
				tmp = ft_itoa(get_status(0, 3));
			else
				tmp = find_env(minishell->env, &line[i]);
			ft_putstr_fd(tmp, fd);
			free(tmp);
			line[j] = c;
			i = j;
			if (!line[i])
				write(fd, "\n", 1);
			i--;
		} else {
			write(fd, &line[i], 1);
		}
		i++;
	}
}

void	ft_here_doc(char **delimiter, t_minishell *minishell)
{
	pid_t	pid;
	int		status;
	char	*tmp;
	char	*line;

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
	int (fd) = open(fd_name, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd == -1)
	{
		free(*delimiter);
		*delimiter = NULL;
		*delimiter = ft_strdup(fd_name);
		free(fd_name);
		return ;
	}
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		minishell->in.saved_stdin = -1;
		minishell->out.saved_stdout = -1;
		signal(SIGINT, control_c_heredoc);
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
			var_doc(minishell, line, fd);
			//write(fd, line, ft_strlen(line));
			free(line);
		}
		get_next_line(0, 1);
		close(fd);
		free(*delimiter);
		*delimiter = fd_name;
		env_lstclear(&minishell->env);
		clear_heredoc_pipe(&minishell->pipe.cmds);
		cmd_lstclear(&minishell->cmd);
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
		exit(get_status(0, 3));
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		get_status(WEXITSTATUS(status), 0);
	free(*delimiter);
	close(fd);
	*delimiter = NULL;
	*delimiter = ft_strdup(fd_name);
	free(fd_name);
	signal(SIGINT, control_c_parent);
	signal(SIGQUIT, SIG_IGN);
}
