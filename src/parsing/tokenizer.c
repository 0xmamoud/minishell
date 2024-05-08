/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:11:19 by mkane             #+#    #+#             */
/*   Updated: 2024/05/08 21:46:30 by mkane            ###   ########.fr       */
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
		// printf("new->content = %s\n", new->cmd);
		token_lstadd_back(&minishell->token, new);
		i++;
	}
	clear_tab(cmds);
	return (1);
}

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
// 		if (str[i + 1] && str[i - 1] && str[i - 1] != ' ' && str[i] == a && str[i + 1] != ' ')
// 		{
// 			split = ft_split(str, a);
// 			while (split[j])
// 			{
// 				r = ft_strjoin(r, split[j]);
// 				if (split[j + 1])
// 					r = ft_strjoin(r, '6');
// 				j++;
// 			}
// 			clear_tab(split);
// 		}
// 		i++;
// 	}
// 	if (ft_strcmp(r, ""))
// 	{
// 		free(r);
// 		r = ft_strdup(str);
// 	}
// 	return (r);
// }

// static char	**add_space(char **split)
// {
// 	int		i;
// 	char	*tmp;

// 	i = 0;
// 	while (split[i])
// 	{
// 		tmp = untruc(split[i], "6|6", '|');
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
	char *tmp;
	int		i;
	int		j;

	i = 0;
	cmd = ft_split(str, ' ');
	add_space(cmd);
	if (!cmd)
		return (NULL);
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == 6)
				cmd[i][j] = ' ';
			j++;
		}
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
