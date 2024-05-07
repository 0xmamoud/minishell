/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:59:50 by tbarret           #+#    #+#             */
/*   Updated: 2024/05/07 11:11:16 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_quoted_chars(char *str, char *new, int *i);
static void	handle_env_vars(char *str, char *new,
				t_minishell *minishell, int *i);
static void	handle_double_quotes(t_minishell *minishell,
				char *str, char *new, int *i);
static int 	after_dollars(char a)
{
	if (a == '\'' || a == '\"' || !a)
		return (0);
	return (1);
}

char	*find_and_replace(char *str, t_minishell *minishell)
{
	char	*new;
	int		i;
	int		len;

	len = count_replace(str, minishell);
	new = ft_calloc(len + 1, sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			handle_quoted_chars(str, new, &i);
		}
		else if (str[i] == '$' && after_dollars(str[i + 1]))
			handle_env_vars(str, new, minishell, &i);
		else
			handle_double_quotes(minishell, str, new, &i);
		i++;
	}
	return (new);
}

static void	handle_double_quotes(t_minishell *minishell, char *str,
				char *new, int *i)
{
	int	quote;

	if (str[*i] == '\"')
	{
		quote = *i;
		(*i)++;
		while (str[*i] && str[*i] != '\"')
		{
			if (str[*i] == '$' && after_dollars(str[*i + 1]))
				handle_env_vars(str, new, minishell, i);
			else
				new[ft_strlen(new)] = str[*i];
			(*i)++;
		}
		if (str[*i] != '\"')
			*i = quote;
	}
	else if (str[*i] != '\"')
		new[ft_strlen(new)] = str[*i];
}

static void	handle_quoted_chars(char *str, char *new, int *i)
{
	while (str[*i] && str[*i] != '\'')
	{
		new[ft_strlen(new)] = str[*i];
		(*i)++;
	}
}

static void	handle_env_vars(char *str, char *new,
				t_minishell *minishell, int *i)
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
		j++;
		while (str[j] && (ft_isalnum(str[j]) || str[j] == '_' || str[j] == '?'))
		{
			char *tmp2 = ft_calloc(2, sizeof(char));
			tmp2[0] = str[j];
			tmp = ft_strjoin(tmp, tmp2);
			free(tmp2);
			j++;
		}
	}
	else
		tmp = find_env(minishell->env, str + j);
	str[*i] = c;
	if (tmp)
	{
		ft_strlcat(new, tmp, ft_strlen(new) + ft_strlen(tmp) + 1);
		free(tmp);
	}
	(*i)--;
}
