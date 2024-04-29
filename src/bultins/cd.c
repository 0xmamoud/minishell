/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:52:30 by mkane             #+#    #+#             */
/*   Updated: 2024/04/27 19:16:19 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cd(t_minishell *minishell)
{
	char	*path;

	char *(pwd) = getcwd(NULL, 0);
	if (!pwd)
		return (free_and_close(minishell));
	t_cmd *(token) = minishell->cmd;
	token = token->next;
	if (!token)
	{
		path = find_env(minishell->env, "HOME");
		chdir(path);
		return (free(pwd), free(path), free_and_close(minishell));
	}
	path = ft_strjoin(pwd, "/");
	if (!path)
		return (free_and_close(minishell));
	path = ft_strjoin(path, token->cmd);
	if (!path)
		return (free_and_close(minishell));
	if (chdir(path) == -1)
	{
		printf("cd: %s: No such file or directory\n", token->cmd);
		return (free(path), ft_exit(1, 0, 0), free_and_close(minishell));
	}
	return (free(path), ft_exit(0, 0, 0), free_and_close(minishell));
}
