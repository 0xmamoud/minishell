/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 18:13:43 by tbarret           #+#    #+#             */
/*   Updated: 2024/05/11 18:16:52 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char *str, t_minishell *minishell, int *i)
{
	int		j;
	char	c;
	char	*tmp;

	(*i)++;
	j = *i;
	while ((ft_isalpha(str[*i]) || str[*i] == '_' || str[*i] == '?'))
		(*i)++;
	c = str[*i];
	str[*i] = '\0';
	if (str[j] == '?')
	{
		tmp = ft_itoa(get_status(0, 3));
		after_interrogation(str, &tmp, &j);
	}
	else
		tmp = find_env(minishell->env, str + j);
	str[*i] = c;
	(*i)--;
	return (tmp);
}

void	append_env_value(char *new, char *tmp)
{
	if (tmp)
	{
		ft_strlcat(new, tmp, ft_strlen(new) + ft_strlen(tmp) + 1);
		free(tmp);
	}
}
