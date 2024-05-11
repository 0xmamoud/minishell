/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:38:09 by tbarret           #+#    #+#             */
/*   Updated: 2024/05/11 18:09:56 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	after_dollars(char a)
{
	if (a == '\'' || a == '\"' || a == 6 || !a)
		return (0);
	return (1);
}

void	after_interrogation(char *str, char **tmp, int *j)
{
	char	*tmp2;

	(*j)++;
	while (str[*j] && (ft_isalnum(str[*j]) || str[*j] == '_' || str[*j] == '?'))
	{
		tmp2 = ft_calloc(2, sizeof(char));
		tmp2[0] = str[*j];
		*tmp = ft_strjoin(*tmp, tmp2);
		free(tmp2);
		(*j)++;
	}
}

int	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	handle_dollars(char **split, t_minishell *minishell)
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
