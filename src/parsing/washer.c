/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   washer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:17:03 by mkane             #+#    #+#             */
/*   Updated: 2024/05/11 17:29:02 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_quotes(char *cmd, char c);
static char	*join_tab(char **tab);

static int	verify_quotes(const char *str)
{
	int	in_single_quote;
	int	in_double_quote;
	int	i;

	i = 0;
	in_double_quote = 0;
	in_single_quote = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (str[i] == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		i++;
	}
	if (in_single_quote || in_double_quote)
		return (0);
	return (1);
}

static char	*add_space_before_and_after_operator(char *str)
{
	char *(new_str) = ft_calloc((ft_strlen(str) * 4), sizeof(char));
	if (!new_str)
		return (NULL);
	int (i) = 0;
	int (j) = 0;
	while (str[i] != '\0')
	{
		if (is_operator(str[i]) && i > 0 && !is_operator(str[i - 1]))
		{
			new_str[j] = ' ';
			j++;
			new_str[j] = str[i];
			if (str[i] == '|')
			{
				j++;
				new_str[j] = ' ';
			}
		}
		else
			new_str[j] = str[i];
		i++;
		j++;
	}
	free(str);
	return (new_str);
}

int	washer(t_minishell *minishell)
{
	char	**split;

	if (!verify_quotes(minishell->line))
		return (0);
	parse(minishell->line, count_quotes(minishell->line, '\"') / 2, '\"');
	parse(minishell->line, count_quotes(minishell->line, '\'') / 2, '\'');
	minishell->line = add_space_before_and_after_operator(minishell->line);
	parse_redirection(minishell->line);
	split = NULL;
	split = ft_split(minishell->line, ' ');
	if (!split)
		return (0);
	free(minishell->line);
	minishell->line = NULL;
	if (!handle_dollars(split, minishell))
		return (clear_tab(split), 0);
	minishell->line = join_tab(split);
	clear_tab(split);
	if (!minishell->line)
		return (0);
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

static char	*join_tab(char **tab)
{
	char	*str;
	int		i;

	str = NULL;
	str = ft_strdup("");
	i = 0;
	if (!str)
		return (NULL);
	while (tab[i])
	{
		str = ft_strjoin(str, tab[i]);
		if (!str)
			return (NULL);
		if (tab[i + 1])
		{
			str = ft_strjoin(str, " ");
			if (!str)
				return (NULL);
		}
		i++;
	}
	return (str);
}
