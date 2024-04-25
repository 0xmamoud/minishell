/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   washer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:17:03 by mkane             #+#    #+#             */
/*   Updated: 2024/04/25 21:02:49 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	checker(char *cmd);
static int	count_quotes(char *cmd, char c);
static void	parse(char *cmd, int ret, char c);
static void	parse_redirection(char *cmd);

static char	*find_and_replace(char *str, t_minishell *minishell)
{
	char	*tmp;

	if (!ft_strchr(str, '$'))
		return (ft_strdup(str));
	char **(split) = ft_split(str, '$');
	if (!split)
		return (NULL);
	char *(new_str) = ft_strdup("");
	if (!new_str)
		return (clear_tab(split), NULL);
	int (i) = -1;
	while (split[++i])
	{
		tmp = find_env(minishell->env, split[i]);
		if (!tmp)
			return (clear_tab(split), free(new_str), NULL);
		new_str = ft_strjoin(new_str, tmp);
		free(tmp);
		if (!new_str)
			return (clear_tab(split), NULL);
	}
	clear_tab(split);
	return (new_str);
}

static char	*handle_dollars(char **split, t_minishell *minishell)
{
	char	*tmp;

	int (i) = -1;
	char *(str) = ft_strdup("");
	if (!str)
		return (NULL);
	while (split[++i])
	{
		if (split[i][0] == '\'')
		{
			str = ft_strjoin(str, split[i]);
			if (!str)
				return (NULL);
		}
		else
		{
			tmp = find_and_replace(split[i], minishell);
			str = ft_strjoin(str, tmp);
			if (tmp)
				free(tmp);
			if (!str)
				return (NULL);
			if (split[i + 1])
			{
				str = ft_strjoin(str, " ");
				if (!str)
					return (NULL);
			}
		}
	}
	return (str);
}

int	washer(t_minishell *minishell)
{
	char	**split;

	if (!checker(minishell->line))
		return (0);
	if (count_quotes(minishell->line, '\'') % 2 != 0
		|| count_quotes(minishell->line, '\"') % 2 != 0)
		return (0);
	parse(minishell->line, count_quotes(minishell->line, '\"') / 2, '\"');
	parse(minishell->line, count_quotes(minishell->line, '\'') / 2, '\'');
	parse_redirection(minishell->line);
	split = ft_split(minishell->line, ' ');
	if (!split)
		return (0);
	free(minishell->line);
	minishell->line = handle_dollars(split, minishell);
	clear_tab(split);
	if (!minishell->line)
		return (0);
	printf("line: %s\n", minishell->line);
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
