/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:52:30 by mkane             #+#    #+#             */
/*   Updated: 2024/04/26 23:47:01 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cd(t_minishell *minishell)
{
	t_cmd	*token;
	char	*path;

	char *(pwd) = getcwd(NULL, 0);
	if (!pwd)
		return (free_and_close(minishell));
	token = minishell->cmd;
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
		ft_exit(minishell, 1, 0, 0);
		printf("cd: %s: No such file or directory\n", token->cmd);
		return (free(path), free_and_close(minishell));
	}
	ft_exit(minishell, 0, 0, 0);
	return (free(path), free_and_close(minishell));
}
