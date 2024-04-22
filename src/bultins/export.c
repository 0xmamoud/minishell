/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:15:19 by mkane             #+#    #+#             */
/*   Updated: 2024/04/22 22:00:46 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token	*get_token(t_minishell *minishell);
static int		add_with_value(t_minishell *minishell, t_token *token);
static void		print_export(t_minishell *minishell);

void	export(t_minishell *minishell)
{
	t_env	*new;

	if (!redirection(minishell))
		return ;
	if (!init_files(minishell))
		return (free_and_close(minishell));
	t_token *(token) = get_token(minishell);
	if (!token)
		return (print_export(minishell), free_and_close(minishell));
	env_lstdelnode(&minishell->env, token->cmd);
	if (ft_strchr(token->cmd, '='))
	{
		if (!add_with_value(minishell, token))
			return (free_and_close(minishell));
	}
	else
	{
		new = env_lstnew(token->cmd, "");
		if (!new)
			return (free_and_close(minishell));
		env_lstadd_back(&minishell->env, new);
	}
	free_and_close(minishell);
}

static void	print_export(t_minishell *minishell)
{
	t_env	*tmp;

	tmp = minishell->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, "", ft_strlen(tmp->content)) == 0)
			ft_printf("declare -x %s\n", tmp->name);
		else
			ft_printf("declare -x %s=\"%s\"\n", tmp->name, tmp->content);
		tmp = tmp->next;
	}
}

static int	add_with_value(t_minishell *minishell, t_token *token)
{
	t_env	*new;
	char	**split;

	split = ft_split(token->cmd, '=');
	if (!split)
		return (0);
	if (!split[1])
		new = env_lstnew(split[0], "");
	else
		new = env_lstnew(split[0], split[1]);
	if (!new)
		return (0);
	env_lstadd_back(&minishell->env, new);
	clear_tab(split);
	return (1);
}

static t_token	*get_token(t_minishell *minishell)
{
	t_token	*token;

	token = minishell->token;
	while (token && token->type != COMMAND)
		token = token->next;
	if (token)
		token = token->next;
	if (token && token->type != COMMAND)
		return (NULL);
	return (token);
}
