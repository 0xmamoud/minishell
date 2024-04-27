/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:59:50 by tbarret           #+#    #+#             */
/*   Updated: 2024/04/27 16:01:54 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_quoted_chars(char *str, char *new, int *i);
static void	handle_env_vars(char *str, char *new,
				t_minishell *minishell, int *i);


// 
char	*find_and_replace(char *str, t_minishell *minishell)
{
	char	*new;
	int		i;
	int		len;
	int		quote;

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
		else if (str[i] == '$')
			handle_env_vars(str, new, minishell, &i);
		else 
		{
			printf("--- %c\n", str[i]);
			if (str[i] == '\"')
			{
				quote = i;
				i++;
				while (str[i] && str[i] != '\"')
				{
					if (str[i] == '$')
						handle_env_vars(str, new, minishell, &i);
					else
						new[ft_strlen(new)] = str[i];
					i++;
				}
				if (str[i] != '\"')
					i = quote;
			} else if (str[i] != '\"')
				new[ft_strlen(new)] = str[i];
		}
		i++;
	}
	return (new);
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
	while ((ft_isalpha(str[*i]) || str[*i] == '_'))
		(*i)++;
	c = str[*i];
	str[*i] = '\0';
	tmp = find_env(minishell->env, str + j);
	str[*i] = c;
	if (tmp)
	{
		ft_strlcat(new, tmp, ft_strlen(new) + ft_strlen(tmp) + 1);
		free(tmp);
	}
	(*i)--;
}
