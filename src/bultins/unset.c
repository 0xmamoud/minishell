/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:37:33 by mkane             #+#    #+#             */
/*   Updated: 2024/04/26 19:17:06 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unset(t_minishell *minishell)
{
	t_token	*token;

	token = minishell->token;
	while (token && token->type != COMMAND)
		token = token->next;
	if (token)
		token = token->next;
	if (!token)
		return (free_and_close(minishell));
	char *(str) = find_env(minishell->env, token->cmd);
	if (!str)
		return (free_and_close(minishell));
	if (ft_strncmp(str, "", ft_strlen(str)) == 0)
		return (free(str), free_and_close(minishell));
	ft_exit(minishell, 1, 0, 0);
	env_lstdelnode(&minishell->env, token->cmd);
	free(str);
	free_and_close(minishell);
}
