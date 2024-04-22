/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:52:30 by mkane             #+#    #+#             */
/*   Updated: 2024/04/22 20:10:17 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token	*get_cd_token(t_minishell *minishell);

void	cd(t_minishell *minishell)
{
	t_token	*token;
	char	*path;

	if (!redirection(minishell))
		return ;
	if (!init_files(minishell))
		return (free_and_close(minishell));
	char *(pwd) = getcwd(NULL, 0);
	if (!pwd)
		return (free_and_close(minishell));
	token = get_cd_token(minishell);
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
	chdir(path);
	return (free(path), free_and_close(minishell));
}

static t_token	*get_cd_token(t_minishell *minishell)
{
	t_token	*token;

	token = minishell->token;
	while (token && token->type != COMMAND)
		token = token->next;
	if (token)
		token = token->next;
	return (token);
}
