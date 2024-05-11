/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:11:19 by mkane             #+#    #+#             */
/*   Updated: 2024/05/11 17:05:28 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**split_cmd(char *str);
static int	token_type(char *str);

static char	replace_char(char c)
{
	if (c == 15)
		return ('|');
	if (c == 16)
		return ('<');
	if (c == 17)
		return ('>');
	if (c == 6)
		return (' ');
	return (c);
}

int	create_token(t_minishell *minishell, char *str)
{
	char	**cmds;
	int		i;
	t_token	*new;

	new = NULL;
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

static char	**split_cmd(char *str)
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
			cmd[i][j] = replace_char(cmd[i][j]);
			j++;
		}
		i++;
	}
	return (cmd);
}

static int	token_type(char *str)
{
	if (is_pipe(str))
		return (PIPE);
	if (is_redirection(str))
		return (REDIRECTION);
	return (COMMAND);
}
