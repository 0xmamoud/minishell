/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:43:44 by mkane             #+#    #+#             */
/*   Updated: 2024/04/27 23:48:24 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_pipe(t_minishell *minishell)
{
	if (!init_pipe(minishell))
		return (pipe_lstclear(&minishell->pipe.cmds));
	if (!pipe_redirection(minishell))
		return (pipe_lstclear(&minishell->pipe.cmds));
	t_pipe_cmds *(pipe) = minishell->pipe.cmds;
	while (pipe)
	{
		printf("cmd: %s\n", pipe->cmd);
		if (pipe->in.file)
			printf("in: %s\n", pipe->in.file);
		if (pipe->out.file)
			printf("out: %s\n", pipe->out.file);
		printf("%d\n", pipe->index);
		printf("====================================\n");
		pipe = pipe->next;
	}
	pipe_lstclear(&minishell->pipe.cmds);
}
