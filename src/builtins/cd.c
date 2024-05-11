/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:52:30 by mkane             #+#    #+#             */
/*   Updated: 2024/05/10 20:59:12 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	change_directory(char *cmd, char *pwd);
static int	update_paths(t_minishell *minishell);

int	cd(t_minishell *minishell)
{
	char	*path;

	if (cmd_lstsize(minishell->cmd) > 2)
		return (ft_print_error("cd: ", NULL, "too many arguments\n"),
			ft_exit(1, 0, 0));
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
	if (!change_directory(token->cmd, pwd))
		return (free(pwd), ft_exit(1, 0, 0));
	free(pwd);
	if (!update_paths(minishell))
		return (ft_putstr_fd("can't update path", 2), ft_exit(1, 0, 0));
	return (ft_exit(0, 0, 0), 1);
}

static int	change_directory(char *cmd, char *pwd)
{
	char	*path;

	path = ft_join(pwd, "/");
	if (!path)
		return (ft_exit(1, 0, 0));
	path = ft_strjoin(path, cmd);
	if (!path)
		return (ft_exit(1, 0, 0));
	if (chdir(path) == -1)
	{
		ft_print_error("cd: ", cmd, "No such file or directory\n");
		free(path);
		return (ft_exit(1, 0, 0));
	}
	free(path);
	return (1);
}

static	int	update_paths(t_minishell *minishell)
{
	char	*oldpwd;
	char	*path;

	oldpwd = find_env(minishell->env, "PWD");
	if (!oldpwd)
		return (ft_exit(1, 0, 0));
	path = getcwd(NULL, 0);
	if (!path)
		return (free(oldpwd), ft_exit(1, 0, 0));
	env_lstdelnode(&minishell->env, "OLDPWD");
	env_lstdelnode(&minishell->env, "PWD");
	env_lstadd_back(&minishell->env, env_lstnew("OLDPWD", oldpwd));
	env_lstadd_back(&minishell->env, env_lstnew("PWD", path));
	free(oldpwd);
	free(path);
	return (1);
}
