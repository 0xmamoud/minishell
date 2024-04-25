/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   washer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:17:03 by mkane             #+#    #+#             */
/*   Updated: 2024/04/25 17:48:36 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	checker(char *cmd);
static int	count_quotes(char *cmd, char c);
static void	parse(char *cmd, int ret, char c);
static void	parse_redirection(char *cmd);

static handle_dollars(t_minishell *minishell)
{
	int	i;
	int	j;
	int	k;
	char	*tmp;

	i = 0;
	while (minishell->line[i])
	{
		if (minishell->line[i] == '$' && minishell->line[i + 1] == '?')
		{
			tmp = ft_itoa(minishell->status);
			j = 0;
			k = 0;
			while (tmp[j])
			{
				minishell->line[i + k] = tmp[j];
				j++;
				k++;
			}
			free(tmp);
		}
		i++;
	}
}

int	washer(t_minishell *minishell)
{
	int		i;
	char	*str;
	char	**split;

	if (!checker(minishell->line))
		return (0);
	if (count_quotes(minishell->line, '\'') % 2 != 0
		|| count_quotes(minishell->line, '\"') % 2 != 0)
		return (0);
	parse(minishell->line, count_quotes(minishell->line, '\"') / 2, '\"');
	parse(minishell->line, count_quotes(minishell->line, '\'') / 2, '\'');
	parse_redirection(minishell->line);
	i = 0;
	split = ft_split(minishell->line, ' ');
	
	return (1);
}

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

static void	parse_redirection(char *cmd)
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
