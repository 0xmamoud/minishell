/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:52:30 by mkane             #+#    #+#             */
/*   Updated: 2024/05/01 21:07:26 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cd(t_minishell *minishell)
{
	char	*path;

	char *(pwd) = getcwd(NULL, 0);
	if (!pwd)
		return (ft_exit(1, 0, 0));
	t_cmd *(token) = minishell->cmd;
	token = token->next;
	if (!token)
	{
		path = find_env(minishell->env, "HOME");
		chdir(path);
		return (free(pwd), free(path), ft_exit(0, 0, 0), 1);
	}
	path = ft_strjoin(pwd, "/");
	if (!path)
		return (free_and_close(minishell), ft_exit(1, 0, 0));
	path = ft_strjoin(path, token->cmd);
	if (!path)
		return (free_and_close(minishell), ft_exit(1, 0, 0));
	if (chdir(path) == -1)
	{
		printf("cd: %s: No such file or directory\n", token->cmd);
		return (free(path), ft_exit(1, 0, 0));
	}
	return (free(path), ft_exit(0, 0, 0), 1);
}
