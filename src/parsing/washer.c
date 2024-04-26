/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   washer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:17:03 by mkane             #+#    #+#             */
/*   Updated: 2024/04/26 16:18:06 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	checker(char *cmd);
static int	count_quotes(char *cmd, char c);
static void	parse(char *cmd, int ret, char c);
static void	parse_redirection(char *cmd);

static char *join_tab(char **tab)
{
	char	*str;
	int		i;

	str = ft_strdup("");
	if (!str)
		return (NULL);
	i = 0;
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

static int	count_replace(char *str, t_minishell *minishell)
{
	char	*tmp;
	int		len;
	char	c;
	int		j;

	len = 0;
	int (i) = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			len++;
			i++;
			while (str[i] && str[i] != '\'')
			{
				len++;
				i++;
			}
		}
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
			len += ft_strlen(tmp);
			free(tmp);
			i--;
		}
		else
		{
			len++;
		}
		i++;
	}
	return (len);
}


static char	*find_and_replace(char *str, t_minishell *minishell)
{
	char	*tmp;
	char	*new;
	char	c;
	int		j;

	int len = count_replace(str, minishell);
	printf("len = %d\n", len);
	new = ft_calloc(len + 1, sizeof(char));
	int (i) = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			new[ft_strlen(new)] = str[i];
			new[ft_strlen(new) + 1] = '\0';
			i++;
			while (str[i] && str[i] != '\'')
			{
				new[ft_strlen(new)] = str[i];
				new[ft_strlen(new) + 1] = '\0';
				i++;
			}
		}
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
			ft_strlcat(new, tmp, ft_strlen(new) + ft_strlen(tmp) + 1);
			free(tmp);
			i--;
		}
		else
		{
			new[ft_strlen(new)] = str[i];
		}
		i++;
	}
	return (new);
}

static int	handle_dollars(char **split, t_minishell *minishell)
{
	int		i;
	int   	j;
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

int	washer(t_minishell *minishell)
{
	char	**split;

	if (!checker(minishell->line))
		return (0);
	if (count_quotes(minishell->line, '\'') % 2 != 0
		|| count_quotes(minishell->line, '\"') % 2 != 0)
		return (0);
	parse(minishell->line, count_quotes(minishell->line, '\"') / 2, '\"');
	parse(minishell->line, count_quotes(minishell->line, '\'') / 2, '\'');
	parse_redirection(minishell->line);
	split = ft_split(minishell->line, ' ');
	if (!split)
		return (0);
	free(minishell->line);
	if (!handle_dollars(split, minishell))
		return (clear_tab(split),0);
	minishell->line = join_tab(split);
	clear_tab(split);
	if (!minishell->line)
		return (0);
	return (1);
}

static int	checker(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == ';' || cmd[i] == '\\' || cmd[i] == '(' || cmd[i] == ')'
			|| cmd[i] == '*' || (cmd[i] == '|' && cmd[i + 1] == '|')
			|| (cmd[i] == '&' && cmd[i + 1] == '&'))
			return (0);
		i++;
	}
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

static void	parse(char *cmd, int ret, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (ret > 0)
	{
		while (cmd[i] && cmd[i] != c)
			i++;
		j = i;
		i++;
		while (cmd[i] && cmd[i] != c)
			i++;
		while (j < i && cmd[j])
		{
			if (cmd[j] == ' ')
				cmd[j] = ';';
			j++;
		}
		if (j == i)
			i++;
		ret--; 
	}
}

static void	parse_redirection(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '<' && cmd[i + 1] == '<' && cmd[i + 2] == ' ')
		{
			i++;
			cmd[i + 1] = ';';
		}
		else if (cmd[i] == '<' && cmd[i + 1] == ' ')
			cmd[i + 1] = ';';
		else if (cmd[i] == '>' && cmd[i + 1] == '>' && cmd[i + 2] == ' ')
		{
			i++;
			cmd[i + 1] = ';';
		}
		else if (cmd[i] == '>' && cmd[i + 1] == ' ')
			cmd[i + 1] = ';';
		i++;
	}
}
