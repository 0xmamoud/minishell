/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:11:19 by mkane             #+#    #+#             */
/*   Updated: 2024/04/17 20:51:30 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token_type	init_type(char *str)
{
	if (is_pipe(str))
		return (PIPE);
	if (is_redirin(str))
		return (REDIR_IN);
	if (is_redirout(str))
		return (REDIR_OUT);
	if (is_heredoc(str))
		return (HEREDOC);
	if (is_redirappend(str))
		return (REDIR_APPEND);
	if (is_subcommand(str))
		return (SUBCOMMAND);
	return (COMMAND);
}

int	create_token(t_minishell *minishell, char *str)
{
	char	**split;
	t_token	*new;
	int		i;

	new = NULL;
	split = NULL;
	split = ft_split(str, ' ');
	if (!split)
		return (0);
	i = -1;
	while (split[++i])
	{
		new = token_lstnew(split[i], init_type(split[i]));
		if (!new)
			return (clear_tab(split), 0);
		token_lstadd_back(&minishell->token, new);
	}
	clear_tab(split);
	return (1);
}
