/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:37:33 by mkane             #+#    #+#             */
/*   Updated: 2024/04/27 17:14:19 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unset(t_minishell *minishell)
{
	t_cmd	*cmds;

	cmds = minishell->cmd;
	cmds = cmds->next;
	if (!cmds)
		return (free_and_close(minishell));
	char *(str) = find_env(minishell->env, cmds->cmd);
	if (!str)
		return (free_and_close(minishell));
	if (ft_strcmp(str, "") == 0)
		return (free(str), free_and_close(minishell));
	env_lstdelnode(&minishell->env, cmds->cmd);
	free(str);
	free_and_close(minishell);
}
