/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:00:32 by mkane             #+#    #+#             */
/*   Updated: 2024/04/21 23:04:45 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_and_close(t_minishell *minishell)
{
	if (minishell->echo.in.fd != -1)
		close(minishell->echo.in.fd);
	if (minishell->echo.out.fd != -1)
	{
		dup2(minishell->echo.out.saved_stdout, STDOUT_FILENO);
		close(minishell->echo.out.saved_stdout);
		close(minishell->echo.out.fd);
	}
	if ((int)minishell->echo.in.type != -1)
		free(minishell->echo.in.file);
	if ((int)minishell->echo.out.type != -1)
		free(minishell->echo.out.file);
}

static char	*get_string(t_minishell *minishell)
{
	char *(str) = ft_strdup("");
	char *(tmp) = NULL;
	if (!str)
		return (NULL);
	t_token *(token) = minishell->token;
	while (token && token->type != COMMAND)
		token = token->next;
	if (token)
		token = token->next;
	if (minishell->echo.option == 1)
		token = token->next;
	while (token)
	{
		if (token->type == COMMAND)
		{
			tmp = replace(minishell, token->cmd);
			if (!tmp)
				return (free(str), NULL);
			str = ft_strjoin(str, tmp);
			if (!str)
				return (free(tmp), NULL);
			free(tmp);
			str = ft_strjoin(str, " ");
		}
		token = token->next;
	}
	return (str);
}

static void	echo_option(t_minishell *minishell)
{
	t_token	*token;

	token = minishell->token;
	while (token && token->type != COMMAND)
		token = token->next;
	if (token)
		token = token->next;
	if (token && token->type == COMMAND && ft_strncmp(token->cmd, "-n",
			ft_strlen(token->cmd)) == 0)
		minishell->echo.option = 1;
	return ;
}

void	echo(t_minishell *minishell)
{
	char	*str;

	if (!echo_redirection(minishell))
		return ;
	echo_option(minishell);
	if (!init_files(minishell))
		return (free_and_close(minishell));
	str = get_string(minishell);
	if (!str)
		return (free_and_close(minishell));
	char *(tmp) = ft_substr(str, 0, ft_strlen(str) - 1);
	if (!tmp)
		return (free(str), free_and_close(minishell));
	if (minishell->echo.option == 1)
		ft_printf("%s", tmp);
	else
		printf("%s\n", tmp);
	free(str);
	free(tmp);
	free_and_close(minishell);
}
