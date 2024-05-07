/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:52:30 by mkane             #+#    #+#             */
/*   Updated: 2024/05/07 20:49:53 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cd(t_minishell *minishell)
{
	char	*path;
	char	*oldpwd;

	if (cmd_lstsize(minishell->cmd) > 2)
	{
		ft_print_error("cd: ", NULL, "too many arguments\n");
		return (ft_exit(1, 0, 0));
	}
	char *(pwd) = getcwd(NULL, 0);
	if (!pwd)
		return (ft_exit(1, 0, 0));
	t_cmd *(token) = minishell->cmd;
	token = token->next;
	if (ft_strcmp(token->cmd, pwd) == 0)
		return (free(pwd), ft_exit(0, 0, 0), 1);
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
		ft_print_error("cd: ", token->cmd, "No such file or directory\n");
		return (free(path), ft_exit(1, 0, 0));
	}
	oldpwd = find_env(minishell->env, "PWD");
	if (!oldpwd)
		return (free(path), ft_exit(1, 0, 0));
	free(path);
	path = getcwd(NULL, 0);
	if (!path)
		return (free(oldpwd), ft_exit(1, 0, 0));
	env_lstdelnode(&minishell->env, "OLDPWD");
	env_lstdelnode(&minishell->env, "PWD");
	env_lstadd_back(&minishell->env, env_lstnew("OLDPWD", oldpwd));
	env_lstadd_back(&minishell->env, env_lstnew("PWD", path));
	free(oldpwd);
	return (free(path), ft_exit(0, 0, 0), 1);
}
