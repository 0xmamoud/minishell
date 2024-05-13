/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process_redirection.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 21:18:31 by mkane             #+#    #+#             */
/*   Updated: 2024/05/13 21:38:38 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_infile_redirection(t_pipe_cmds **cmds)
{
	if ((*cmds)->in.file)
	{
		(*cmds)->in.fd = open((*cmds)->in.file, O_RDONLY);
		if ((*cmds)->in.fd == -1)
		{
			perror((*cmds)->in.file);
			return (ft_exit(1, 0, 0));
		}
		if (dup2((*cmds)->in.fd, STDIN_FILENO) == -1)
		{
			perror((*cmds)->in.file);
			return (ft_exit(errno, 0, 0));
		}
		close((*cmds)->in.fd);
	}
	return (1);
}

int	pipe_outfile_redirection(t_pipe_cmds **cmds)
{
	if ((*cmds)->out.file)
	{
		if ((*cmds)->out.type == REDIR_OUT)
			(*cmds)->out.fd = open((*cmds)->out.file,
					O_WRONLY | O_CREAT | O_TRUNC, 0777);
		else
			(*cmds)->out.fd = open((*cmds)->out.file,
					O_WRONLY | O_CREAT | O_APPEND, 0777);
		if ((*cmds)->out.fd == -1)
		{
			perror((*cmds)->out.file);
			if ((*cmds)->in.fd != -1)
				close((*cmds)->in.fd);
			return (ft_exit(1, 0, 0));
		}
		if (dup2((*cmds)->out.fd, STDOUT_FILENO) == -1)
		{
			perror((*cmds)->out.file);
			return (ft_exit(errno, 0, 0));
		}
		close((*cmds)->out.fd);
	}
	return (1);
}
