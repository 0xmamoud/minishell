/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   washer2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:05:30 by tbarret           #+#    #+#             */
/*   Updated: 2024/05/09 18:50:44 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
			if (cmd[j] == '|')
				cmd[j] = 15;
			if (cmd[j] == '<')
				cmd[j] = 16;
			if (cmd[j] == '>')
				cmd[j] = 17;
			if (cmd[j] == ' ')
				cmd[j] = 6;
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
