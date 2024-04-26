/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:30:16 by mkane             #+#    #+#             */
/*   Updated: 2024/04/26 18:31:53 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_env_chars(char *str, t_minishell *minishell, int i);
static int	count_quoted_chars(char *str, int start);

int	count_replace(char *str, t_minishell *minishell)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			len += count_quoted_chars(str, i + 1);
			while (str[i] && str[i] != '\'')
				i++;
		}
		else if (str[i] == '$')
			len += count_env_chars(str, minishell, i);
		else
			len++;
		i++;
	}
	return (len);
}

static int	count_quoted_chars(char *str, int start)
{
	int	len;
	int	i;

	len = 0;
	i = start;
	while (str[i] && str[i] != '\'')
	{
		len++;
		i++;
	}
	return (len);
}

static int	count_env_chars(char *str, t_minishell *minishell, int i)
{
	int		len;
	int		j;
	char	*tmp;
	char	c;

	len = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (str[i] == '$')
	{
		i++;
		j = i;
		while ((ft_isalpha(str[i]) || str[i] == '_'))
			i++;
		c = str[i];
		str[i] = '\0';
		tmp = find_env(minishell->env, str + j);
		str[i] = c;
		if (tmp)
		{
			len += ft_strlen(tmp);
			free(tmp);
		}
	}
	return (len);
}
