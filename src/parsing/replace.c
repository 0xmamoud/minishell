/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:30:16 by mkane             #+#    #+#             */
/*   Updated: 2024/05/09 18:50:44 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// oqwj
static int	count_env_chars(char *str, t_minishell *minishell, int i);
static int	count_quoted_chars(char *str, int start);
static int 	after_dollars(char a)
{
	if (a == '\'' || a == '\"' || a == 6 || !a)
		return (0);
	return (1);
}



int	count_replace(char *str, t_minishell *minishell)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (str[i])
	{
		// if (str[i + 2] && ((str[i] == '\'' && str[i + 2] == '\'') || (str[i] == '\"' && str[i + 2] == '\"')))
		// {
		// 	len += 3;
		// 	i += 3;
		// 	continue;
		// }
		if (str[i] == '\'')
		{
			len += count_quoted_chars(str, i + 1);
			while (str[i] && str[i] != '\'')
				i++;
		}
		else if (str[i] == '$' && after_dollars(str[i + 1])) {
			len += count_env_chars(str, minishell, i);
		} else
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
	tmp = NULL;
	while (str[i] && str[i] != '$')
		i++;
	if (str[i] == '$' && after_dollars(str[i + 1]))
	{
		i++;
		j = i;
		while ((ft_isalpha(str[i]) || str[i] == '_' || str[i] == '?'))
			i++;
		c = str[i];
		str[i] = '\0';
		if (str[j] == '?')
		{
			tmp = ft_itoa(get_status(0, 3));
			j++;
			while (str[j] && (ft_isalnum(str[j]) || str[j] == '_' || str[j] == '?'))
			{
				char *tmp2 = ft_calloc(2, sizeof(char));
				tmp2[0] = str[j];
				tmp = ft_strjoin(tmp, tmp2);
				free(tmp2);
				j++;
			}
		} else
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
