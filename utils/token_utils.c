/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:17:03 by mkane             #+#    #+#             */
/*   Updated: 2024/04/27 19:08:23 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_pipe(char *str)
{
	if (!str)
		return (0);
	if (ft_strncmp(str, "|", 1) == 0)
		return (1);
	return (0);
}

int	is_redirection(char *str)
{
	if (!str)
		return (0);
	if (str[0] == '>' && str[1] == '>')
		return (1);
	if (str[0] == '>' && str[1] != '>')
		return (1);
	if (str[0] == '<' && str[1] != '<')
		return (1);
	if (str[0] == '<' && str[1] == '<')
		return (1);
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
