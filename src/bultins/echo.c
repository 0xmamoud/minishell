/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:00:32 by mkane             #+#    #+#             */
/*   Updated: 2024/04/25 18:20:33 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char		*get_string(t_minishell *minishell);
static t_token	*get_sub_string(t_minishell *minishell);
static void		echo_option(t_minishell *minishell);

void	echo(t_minishell *minishell)
{
	char	*str;

	if (!redirection(minishell))
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
	ft_exit(minishell, 0, 0, 0);
	free(str);
	free(tmp);
	free_and_close(minishell);
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

static char	*get_string(t_minishell *minishell)
{
	char *(str) = ft_strdup("");
	if (!str)
		return (NULL);
	t_token *(token) = get_sub_string(minishell);
	while (token)
	{
		if (token->type == COMMAND)
		{
			str = ft_strjoin(str, token->cmd);
			if (!str)
				return (NULL);
			str = ft_strjoin(str, " ");
		}
		token = token->next;
	}
	return (str);
}

static	t_token	*get_sub_string(t_minishell *minishell)
{
	t_token	*token;

	token = minishell->token;
	while (token && token->type != COMMAND)
		token = token->next;
	if (token)
		token = token->next;
	if (minishell->echo.option == 1)
		token = token->next;
	return (token);
}
