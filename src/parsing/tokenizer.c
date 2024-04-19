/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:11:19 by mkane             #+#    #+#             */
/*   Updated: 2024/04/19 18:40:42 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	char	**split_cmd(char *str)
{
	char	**cmd;
	int		i;
	int		j;

	i = 0;
	cmd = ft_split(str, ' ');
	if (!cmd)
		return (NULL);
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == ';')
				cmd[i][j] = ' ';
			j++;
		}
		i++;
	}
	return (cmd);
}

static	int	token_type(char *str)
{
	if (is_pipe(str))
		return (PIPE);
	if (is_redirection(str))
		return (REDIRECTION);
	return (COMMAND);
}

int	create_token(t_minishell *minishell, char *str)
{
	char	**cmds;
	int		i;
	t_token	*new;

	cmds = split_cmd(str);
	if (!cmds)
		return (0);
	i = 0;
	while (cmds[i])
	{
		new = token_lstnew(cmds[i], token_type(cmds[i]));
		if (!new)
		{
			clear_tab(cmds);
			return (0);
		}
		token_lstadd_back(&minishell->token, new);
		i++;
	}
	clear_tab(cmds);
	return (1);
}
