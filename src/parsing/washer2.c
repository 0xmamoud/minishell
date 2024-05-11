/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   washer2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:05:30 by tbarret           #+#    #+#             */
/*   Updated: 2024/05/11 17:13:24 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	replace_char(char c)
{
	if (c == '|')
		return (15);
	if (c == '<')
		return (16);
	if (c == '>')
		return (17);
	if (c == ' ')
		return (6);
	return (c);
}

void	parse(char *cmd, int ret, char c)
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
			cmd[j] = replace_char(cmd[j]);
			j++;
		}
		if (j == i)
			i++;
		ret--;
	}
}

void	parse_redirection(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '>' || cmd[i] == '<')
		{
			i++;
			if (cmd[i] == '>' || cmd[i] == '<')
				i++;
			while (cmd[i] == ' ')
			{
				cmd[i] = 6;
				i++;
			}
		}
		i++;
	}
}
