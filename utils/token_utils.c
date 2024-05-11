/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:17:03 by mkane             #+#    #+#             */
/*   Updated: 2024/05/11 20:07:15 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_pipe(char *str)
{
	if (!str)
		return (0);
	if (ft_strcmp(str, "|") == 0)
		return (1);
	return (0);
}

static int	is_redirection_bool(char *str, int *i)
{
	while (str[*i] && str[*i] == ' ')
			(*i)++;
	if (str[*i] == '\0')
		return (1);
	while (str[*i])
	{
		if (str[*i] == '|' || str[*i] == '<' || str[*i] == '>')
			return (0);
		(*i)++;
	}
	return (1);
}

int	is_redirection(char *str)
{
	int	i;

	if (!str)
		return (0);
	else if ((str[0] == '>' && str[1] == '>')
		|| (str[0] == '<' && str[1] == '<'))
	{
		i = 2;
		return (is_redirection_bool(str, &i));
	}
	else if ((str[0] == '>' && str[1] != '>')
		|| (str[0] == '<' && str[1] != '<'))
	{
		i = 1;
		return (is_redirection_bool(str, &i));
	}
	return (0);
}

int	cmd_len(t_minishell *minishell)
{
	int		len;
	t_token	*token;

	len = 0;
	token = minishell->token;
	while (token)
	{
		if (token->type == COMMAND)
			len++;
		token = token->next;
	}
	return (len);
}
