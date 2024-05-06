/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   washer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:17:03 by mkane             #+#    #+#             */
/*   Updated: 2024/05/06 21:49:21 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static int	checker(char *cmd);
static int	count_quotes(char *cmd, char c);
static char	*join_tab(char **tab);
static int	handle_dollars(char **split, t_minishell *minishell);


static int verify_quotes(const char *str) {
    int in_single_quote;
    int in_double_quote;
    int i;

	i = 0;
	in_double_quote = 0;
	in_single_quote = 0;
    while (str[i] != '\0') {
        if (str[i] == '\'' && !in_double_quote) {
            in_single_quote = !in_single_quote;
        } else if (str[i] == '\"' && !in_single_quote) {
            in_double_quote = !in_double_quote;
        }
        i++;
    }

    if (in_single_quote || in_double_quote)
        return (0);

    return (1);
}


int	washer(t_minishell *minishell)
{
	char	**split;

	// if (!checker(minishell->line))
	// 	return (0);
	if (!verify_quotes(minishell->line))
		return (0);
	parse(minishell->line, count_quotes(minishell->line, '\"') / 2, '\"');
	parse(minishell->line, count_quotes(minishell->line, '\'') / 2, '\'');
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

// static int	checker(char *cmd)
// {
// 	int	i;

// 	i = 0;
// 	while (cmd[i])
// 	{
// 		if (cmd[i] == ';' || cmd[i] == '\\' || cmd[i] == '(' || cmd[i] == ')'
// 			|| (cmd[i] == '|' && cmd[i + 1] == '|')
// 			|| (cmd[i] == '&' && cmd[i + 1] == '&'))
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

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

static int	handle_dollars(char **split, t_minishell *minishell)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	j = 0;
	while (split[++i])
	{
		tmp = find_and_replace(split[i], minishell);
		if (!tmp)
			return (0);
		free(split[i]);
		split[i] = ft_strdup(tmp);
		free(tmp);
		if (!split[i])
			return (0);
	}
	return (1);
}
