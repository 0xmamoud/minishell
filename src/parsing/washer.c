/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   washer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:17:03 by mkane             #+#    #+#             */
/*   Updated: 2024/04/19 21:32:39 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	checker(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == ';' || cmd[i] == '\\' || cmd[i] == '(' || cmd[i] == ')'
			|| cmd[i] == '*' || (cmd[i] == '|' && cmd[i + 1] == '|')
			|| (cmd[i] == '&' && cmd[i + 1] == '&'))
			return (0);
		i++;
	}
	return (1);
}

static int	count_quotes(char *cmd, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if (cmd[i] == c)
			count++;
		i++;
	}
	return (count);
}

static void	parse(char *cmd, int ret, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (ret > 0)
	{
		while (cmd[i] && cmd[i] != c)
			i++;
		j = i;
		i++;
		while (cmd[i] && cmd[i] != c)
			i++;
		while (j < i && cmd[j])
		{
			if (cmd[j] == ' ')
				cmd[j] = ';';
			j++;
		}
		if (j == i)
			i++;
		ret--;
	}
}

static void	redirection(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '<' && cmd[i + 1] == '<' && cmd[i + 2] == ' ')
		{
			i++;
			cmd[i + 1] = ';';
		}
		else if (cmd[i] == '<' && cmd[i + 1] == ' ')
			cmd[i + 1] = ';';
		else if (cmd[i] == '>' && cmd[i + 1] == '>' && cmd[i + 2] == ' ')
		{
			i++;
			cmd[i + 1] = ';';
		}
		else if (cmd[i] == '>' && cmd[i + 1] == ' ')
			cmd[i + 1] = ';';
		i++;
	}
}

int	washer(char *cmd)
{
	if (!checker(cmd))
		return (0);
	if (count_quotes(cmd, '\'') % 2 != 0 || count_quotes(cmd, '\"') % 2 != 0)
		return (0);
	parse(cmd, count_quotes(cmd, '\"') / 2, '\"');
	parse(cmd, count_quotes(cmd, '\'') / 2, '\'');
	redirection(cmd);

	return (1);
}
