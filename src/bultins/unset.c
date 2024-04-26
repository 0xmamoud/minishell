/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:37:33 by mkane             #+#    #+#             */
/*   Updated: 2024/04/26 23:58:41 by mkane            ###   ########.fr       */
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
	// ft_exit(minishell, 1, 0, 0);
	env_lstdelnode(&minishell->env, cmds->cmd);
	free(str);
	free_and_close(minishell);
}
