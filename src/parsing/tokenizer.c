/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:11:19 by mkane             #+#    #+#             */
/*   Updated: 2024/05/09 18:50:44 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**split_cmd(char *str);
static int	token_type(char *str);

int	create_token(t_minishell *minishell, char *str)
{
	char	**cmds;
	int		i;
	t_token	*new;

	new = NULL;
	cmds = split_cmd(str);
	if (!cmds)
		return (0);
	i = 0;
	while (cmds[i])
	{
		new = token_lstnew(cmds[i], token_type(cmds[i]));
		if (!new)
		{
			clear_tab(cmds);
			return (0);
		}
		token_lstadd_back(&minishell->token, new);
		i++;
	}
	clear_tab(cmds);
	return (1);
}

// static int ft_menumaxibestof(char c)
// {
// 	if (c == 6 || c == 15 || c == 16 || c== 17 || c == ' ' || c == '<' || c == '>')
// 		return (1);
// 	return (0);
// }

// static char *untruc(char *str, char *c, char a)
// {
// 	char **split;
// 	int i;
// 	int j;
// 	char *r;
// 	i = 0;
// 	j = 0;
// 	r = ft_strdup("");
// 	while (str[i])
// 	{
// 		if (str[i + 1] && str[i - 1] && !ft_menumaxibestof(str[i - 1]) && !ft_menumaxibestof(str[i + 1]))
// 		{
// 			split = ft_split(str, a);
// 			while (split[j])
// 			{
// 				r = ft_strjoin(r, split[j]);
// 				if (split[j + 1])
// 					r = ft_strjoin(r, c);
// 				j++;
// 			}
// 			clear_tab(split);
// 		}
// 		i++;
// 	}
// 	if (ft_strlen(r) == 0)
// 	{
// 		free(r);
// 		r = ft_strdup(str);
// 	}
// 	return (r);
// }

// static void print_tab(char **tab)
// {
// 	int i = 0;
// 	while (tab[i])
// 	{
// 		printf("tab[%d] = %s\n", i, tab[i]);
// 		i++;
// 	}
// }

// static char *join_tab(char **tab, char *c)
// {
// 	char *str;
// 	int i;

// 	str = NULL;
// 	str = ft_strdup("");
// 	i = 0;
// 	if (!str)
// 		return (NULL);
// 	while (tab[i])
// 	{
// 		str = ft_strjoin(str, tab[i]);
// 		if (tab[i + 1])
// 			str = ft_strjoin(str, c);
// 		i++;
// 	}
// 	return (str);
// }

// static char	**add_space(char **split)
// {
// 	int		i;
// 	char	*tmp;

// 	i = 0;
// 	while (split[i])
// 	{
// 		tmp = untruc(split[i], " | ", '|');
// 		tmp = untruc(tmp, " < ", '<');
// 		tmp = untruc(tmp, " > ", '>');
// 		free(split[i]);
// 		split[i] = ft_strdup(tmp);
// 		free(tmp);
// 		i++;
// 	}
// 	return (split);
// }


static char	**split_cmd(char *str)
{
	char	**cmd;
	int		i;
	int		j;

	i = 0;
	cmd = ft_split(str, ' ');
	// cmd = ft_split(join_tab(add_space(cmd), " "), ' ');
	if (!cmd)
		return (NULL);
	// print_tab(cmd);
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == 15)
				cmd[i][j] = '|';
			if (cmd[i][j] == 16)
				cmd[i][j] = '<';
			if (cmd[i][j] == 17)
				cmd[i][j] = '>';
			if (cmd[i][j] == 6)
				cmd[i][j] = ' ';
			j++;
		}
		// printf("cmd[%d] = %s\n", i, cmd[i]);
		i++;
	}
	
	return (cmd);
}

static int	token_type(char *str)
{
	if (is_pipe(str))
		return (PIPE);
	if (is_redirection(str))
		return (REDIRECTION);
	return (COMMAND);
}
