/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:43:44 by mkane             #+#    #+#             */
/*   Updated: 2024/04/30 20:11:50 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static	void	expend_pipe(t_minishell *minishell, )

// static int	setup_commands(t_minishell *minishell, char **args)
// {
// 	(void) minishell;
// 	(void) args;
// 	return 0;	
// }

//  

void	minishell_pipe(t_minishell *minishell)
{
	if (!init_pipe(minishell))
		return (pipe_lstclear(&minishell->pipe.cmds));
	if (!pipe_redirection(minishell))
		return (pipe_lstclear(&minishell->pipe.cmds));
	if (!pipe_types(minishell))
		return (pipe_lstclear(&minishell->pipe.cmds));
	pipe_lstclear(&minishell->pipe.cmds);
}
