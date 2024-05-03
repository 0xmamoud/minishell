/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:02:42 by mkane             #+#    #+#             */
/*   Updated: 2024/05/04 00:41:15 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_minishell(t_minishell *minishell)
{
	free(minishell->line);
	token_lstclear(&minishell->token);
	cmd_lstclear(&minishell->cmd);
	free_and_close(minishell);
	pipe_lstclear(&minishell->pipe.cmds);
	env_lstclear(&minishell->env);
	exit(0);
}
