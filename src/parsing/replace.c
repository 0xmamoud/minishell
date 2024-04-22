/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:30:16 by mkane             #+#    #+#             */
/*   Updated: 2024/04/22 16:49:38 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*sub_replace(t_minishell *minishell, char *str);

char	*replace(t_minishell *minishell, char *str)
{
	int		j;
	char	*tmp;
	char	*tmp2;

	int (i) = -1;
	if (str[0] == '$' || str[0] == '\'')
		return (sub_replace(minishell, str));
	if (str[0] == '\"')
	{
		while (str[++i])
		{
			if (str[i] == '$')
			{
				j = i + 1;
				while (str[j] && str[j] != '\"' && str[j] != '\'')
					j++;
				tmp = ft_substr(str, i + 1, j - i - 1);
				tmp2 = find_env(minishell->env, tmp);
				if (tmp)
					free(tmp);
				return (tmp2);
			}
		}
	}
	return (ft_strdup(str));
}

static char	*sub_replace(t_minishell *minishell, char *str)
{
	if (str[0] == '$')
		return (find_env(minishell->env, &str[1]));
	return (ft_strtrim(str, "\'"));
}
