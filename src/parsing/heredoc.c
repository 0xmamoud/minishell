/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:18:26 by tbarret           #+#    #+#             */
/*   Updated: 2024/04/27 17:56:12 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_here_doc(char **delimiter)
{
	char	*line;
	int		fd;
	char *fd_name;
	
	fd_name = ft_strjoin(ft_strdup("here_doc."), *delimiter);
	fd = open(fd_name, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd == -1)
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
	get_status(0, 0);
	close(fd);
	free(*delimiter);
	*delimiter = fd_name; 
}