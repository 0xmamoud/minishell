/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:12:38 by mkane             #+#    #+#             */
/*   Updated: 2024/05/09 17:35:08 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*token_lstnew(char *cmd, t_token_type type)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->cmd = ft_strdup(cmd);
	if (!new->cmd)
	{
		free(new);
		return (NULL);
	}
	new->type = type;
	new->next = NULL;
	return (new);
}

t_token	*token_lstlast(t_token *token)
{
	t_token	*tmp;

	if (!token)
		return (NULL);
	tmp = token;
	while (tmp->next && tmp)
		tmp = tmp->next;
	return (tmp);
}

void	token_lstadd_back(t_token **token, t_token *new)
{
	t_token	*tmp;

	tmp = NULL;
	if (!token || !new)
		return ;
	if (!*token)
	{
		*token = new;
		return ;
	}
	tmp = token_lstlast(*token);
	tmp->next = new;
}

void	token_lstclear(t_token **token)
{
	t_token	*tmp;

	tmp = NULL;
	if (!token || !*token)
		return ;
	while (*token)
	{
		tmp = (*token)->next;
		if ((*token)->cmd)
			free((*token)->cmd);
		free(*token);
		*token = tmp;
	}
}
