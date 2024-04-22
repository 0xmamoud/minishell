/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:02:42 by mkane             #+#    #+#             */
/*   Updated: 2024/04/22 17:21:12 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_minishell(t_minishell *minishell)
{
	if (!redirection(minishell))
		return ;
	if (!init_files(minishell))
		return (free_and_close(minishell));
	free(minishell->line);
	token_lstclear(&minishell->token);
	free_and_close(minishell);
	env_lstclear(&minishell->env);
	exit(0);
}
