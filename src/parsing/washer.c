/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   washer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:17:03 by mkane             #+#    #+#             */
/*   Updated: 2024/04/17 16:01:36 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	quote_count(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

static char	*process_split_strings(char **tmp, char *new,
		t_minishell *minishell)
{
	char	*content;
	int		i;

	i = -1;
	while (tmp[++i])
	{
		if (tmp[i][0] == '$')
		{
			content = find_env(minishell->env, tmp[i] + 1);
			if (!content)
				return (free(new), NULL);
			free(tmp[i]);
			tmp[i] = ft_strdup(content);
			if (!tmp[i])
				return (free(new), NULL);
		}
		new = ft_strjoin(new, " ");
		if (!new)
			break ;
		new = ft_strjoin(new, tmp[i]);
		if (!new)
			break ;
	}
	return (new);
}

static char	*replace(char *str, char charset, t_minishell *minishell)
{
	char	*new;
	char	**tmp;

	new = ft_strdup("");
	if (!new)
		return (NULL);
	tmp = ft_split(str, charset);
	if (!tmp)
		return (free(new), NULL);
	new = process_split_strings(tmp, new, minishell);
	return (clear_tab(tmp), new);
}

static char	*remove_single_quote(char *str)
{
	int		len_quote;
	int		i;
	int		j;
	char	*new;

	len_quote = quote_count(str, '\'');
	new = malloc(sizeof(char) * (ft_strlen(str) - len_quote + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\'')
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	return (new);
}

char	*washer(char *str, t_minishell *minishell)
{
	char	*tmp1;
	char	*tmp2;
	char	*new;

	if (quote_count(str, '\"') % 2 != 0 || quote_count(str, '\'') % 2 != 0)
		return (NULL);
	tmp1 = replace(str, '\"', minishell);
	if (!tmp1)
		return (NULL);
	tmp2 = replace(tmp1, ' ', minishell);
	free(tmp1);
	if (!tmp2)
		return (NULL);
	if (quote_count(tmp2, '\'') == 0)
		return (tmp2);
	new = remove_single_quote(tmp2);
	free(tmp2);
	return (new);
}
