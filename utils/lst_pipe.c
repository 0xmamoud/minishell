/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 20:26:19 by mkane             #+#    #+#             */
/*   Updated: 2024/05/07 22:14:23 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipe_cmds	*pipe_lstnew(char *cmd, int index)
{
	t_pipe_cmds	*new;

	new = (t_pipe_cmds *)malloc(sizeof(t_pipe_cmds));
	if (!new)
		return (NULL);
	new->cmd = ft_strdup(cmd);
	if (!new->cmd)
		return (free(new), NULL);
	new->index = index;
	new->in.file = NULL;
	new->in.fd = -1;
	new->out.file = NULL;
	new->out.fd = -1;
	new->next = NULL;
	return (new);
}

t_pipe_cmds	*pipe_lstlast(t_pipe_cmds *pipe)
{
	t_pipe_cmds	*tmp;

	if (!pipe)
		return (NULL);
	tmp = pipe;
	while (tmp->next && tmp)
		tmp = tmp->next;
	return (tmp);
}

void	pipe_lstadd_back(t_pipe_cmds **pipe, t_pipe_cmds *new)
{
	t_pipe_cmds	*tmp;
	int			index;

	tmp = NULL;
	if (!pipe || !new)
		return ;
	if (!*pipe)
	{
		*pipe = new;
		return ;
	}
	tmp = pipe_lstlast(*pipe);
	tmp->next = new;
	index = 0;
	tmp = *pipe;
	while (tmp)
	{
		tmp->index = index;
		tmp = tmp->next;
		index++;
	}
}

static void	free_pipe(t_pipe_cmds **pipe)
{
	t_pipe_cmds	*tmp;

	if (!pipe || !*pipe)
		return ;
	if (*pipe)
	{
		tmp = (*pipe)->next;
		if ((*pipe)->cmd)
			free((*pipe)->cmd);
		free(*pipe);
		*pipe = tmp;
	}
}

void	pipe_lstclear(t_pipe_cmds **pipe)
{
	if (!pipe || !*pipe)
		return ;
	while (*pipe)
	{
		if ((*pipe)->in.file)
		{
			if ((*pipe)->in.type == HEREDOC)
				unlink((*pipe)->in.file);
			if ((*pipe)->in.file)
				free((*pipe)->in.file);
		}
		if ((*pipe)->out.file)
			free((*pipe)->out.file);
		free_pipe(pipe);
	}
}
