/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:00:32 by mkane             #+#    #+#             */
/*   Updated: 2024/04/20 23:12:26 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	void	free_and_close(t_minishell *minishell)
{
	if (minishell->echo.in.fd != -1)
		close(minishell->echo.in.fd);
	if (minishell->echo.out.fd != -1)
		close(minishell->echo.out.fd);
	if ((int) minishell->echo.in.type != -1)
		free(minishell->echo.in.file);
	if ((int) minishell->echo.out.type != -1)
		free(minishell->echo.out.file);
}

static int	init_files(t_minishell *minishell)
{
	if ((int)minishell->echo.in.type != -1)
	{
		if (minishell->echo.in.type == REDIR_IN)
			minishell->echo.in.fd = open(minishell->echo.in.file, O_RDONLY);
		if (minishell->echo.in.type == HEREDOC)
			minishell->echo.in.fd = open(minishell->echo.in.file, O_RDONLY);
		if (minishell->echo.in.fd == -1)
			return (ft_putstr_fd(": No such file or directory\n", 2), 0);
		dup2(minishell->echo.in.fd, STDIN_FILENO);
	}
	if ((int)minishell->echo.out.type != -1)
	{
		if (minishell->echo.out.type == REDIR_OUT)
			minishell->echo.out.fd = open(minishell->echo.out.file,
					O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (minishell->echo.out.type == REDIR_OUT_APPEND)
			minishell->echo.out.fd = open(minishell->echo.out.file,
					O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (minishell->echo.out.fd == -1)
			return (ft_putstr_fd(": No such file or directory\n", 2), 0);
		dup2(minishell->echo.out.fd, STDOUT_FILENO);
	}
	return (1);
}

static	char	*parse(t_minishell *minishell, char *str)
{
	char	*new_str;
	char	*tmp;

	if (str[0] == '\"')
	{
		tmp = ft_strtrim(str, "\"");
		if (!tmp)
			return (NULL);
		new_str = find_env(minishell->env, tmp);
		free(tmp);
		if (!new_str)
			return ("");
		return (new_str);
	}
	else if (str[0] == '\'')
	{
		tmp = ft_strtrim(str, "\'");
		if (!tmp)
			return (NULL);
		return (tmp);
	}
	else if (str[0] == '$')
	{
		new_str = find_env(minishell->env, str);
		if (!new_str)
			return ("");
		return (new_str);
	}
	else
	{
		new_str = ft_strdup(str);
		if (!new_str)
			return (NULL);
		return (new_str);
	}
}

static	char	*get_string(t_minishell *minishell)
{
	t_token	*token;

	char *(str) = NULL;
	token = minishell->token;
	while (token && token->type != COMMAND)
		token = token->next;
	if (token)
		token = token->next;
	if (token && token->type == COMMAND && ft_strncmp(token->cmd, "-n",
			ft_strlen(token->cmd)) == 0)
	{
		minishell->echo.option = 1;
		token = token->next;
	}
	while (token && token->type == COMMAND)
	{
		str = parse(minishell, token->cmd);
		if (!str)
			return (NULL);
		str = ft_strjoin(str, " ");
		if (!str)
			return (NULL);
		token = token->next;
	}
	return (str);
}

void	echo(t_minishell *minishell)
{
	char	*str;

	if (!echo_redirection(minishell))
		return ;
	if (!init_files(minishell))
	{
		free_and_close(minishell);
		return ;
	}
	str = get_string(minishell);
	if (!str)
	{
		free_and_close(minishell);
		return ;
	}
	if (minishell->echo.option == 1)
		printf("%s", str);
	else
		printf("%s\n", str);
}
