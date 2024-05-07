/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:54:22 by tbarret           #+#    #+#             */
/*   Updated: 2024/05/07 22:12:44 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*cmd_lstnew(char *cmd)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->cmd = ft_strdup(cmd);
	if (!new->cmd)
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

t_cmd	*cmd_lstlast(t_cmd *cmd)
{
	t_cmd	*tmp;

	if (!cmd)
		return (NULL);
	tmp = cmd;
	while (tmp->next && tmp)
		tmp = tmp->next;
	return (tmp);
}

void	cmd_lstadd_back(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*tmp;

	tmp = NULL;
	if (!cmd || !new)
		return ;
	if (!*cmd)
	{
		*cmd = new;
		return ;
	}
	tmp = cmd_lstlast(*cmd);
	tmp->next = new;
}

void	cmd_lstclear(t_cmd **cmd)
{
	t_cmd	*tmp;

	if (!cmd || !*cmd)
		return ;
	while (*cmd)
	{
		tmp = (*cmd)->next;
		if ((*cmd)->cmd)
			free((*cmd)->cmd);
		free(*cmd);
		*cmd = tmp;
	}
}

int	cmd_lstsize(t_cmd *cmd)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	tmp = cmd;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
