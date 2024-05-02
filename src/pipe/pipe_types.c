/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_types.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 19:10:46 by mkane             #+#    #+#             */
/*   Updated: 2024/04/30 20:10:09 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_builtin	get_cmd_type(char *cmd);

int	pipe_types(t_minishell *minishell)
{
	t_pipe_cmds	*cmds;
	char		**args;

	cmds = minishell->pipe.cmds;
	while (cmds)
	{
		args = ft_split(cmds->cmd, ' ');
		if (!args)
			return (0);
		cmds->type = get_cmd_type(args[0]);
		clear_tab(args);
		cmds = cmds->next;
	}
	return (1);
}

static t_builtin	get_cmd_type(char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (ECHO);
	if (!ft_strcmp(cmd, "cd"))
		return (CD);
	if (!ft_strcmp(cmd, "pwd"))
		return (PWD);
	if (!ft_strcmp(cmd, "export"))
		return (EXPORT);
	if (!ft_strcmp(cmd, "unset"))
		return (UNSET);
	if (!ft_strcmp(cmd, "env"))
		return (ENV);
	if (!ft_strcmp(cmd, "exit"))
		return (EXIT);
	return (BUILTIN_COUNT);
}