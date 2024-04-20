/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:49:23 by mkane             #+#    #+#             */
/*   Updated: 2024/04/20 21:50:29 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	infile_case(t_minishell *minishell, char *file)
{
	int	i;

	i = 1;
	if (file[i] == ' ')
		i++;
	minishell->echo.in.file = strdup(&file[i]);
	if (!minishell->echo.in.file)
		return (0);
	minishell->echo.in.type = REDIR_IN;
	return (1);
}

int	outfile_case(t_minishell *minishell, char *file)
{
	int	i;

	i = 1;
	if (file[i] == ' ')
		i++;
	minishell->echo.out.file = strdup(&file[i]);
	if (!minishell->echo.out.file)
		return (0);
	minishell->echo.out.type = REDIR_OUT;
	return (1);
}

int	outfile_append_case(t_minishell *minishell, char *file)
{
	int	i;

	i = 2;
	if (file[i] == ' ')
		i++;
	minishell->echo.out.file = strdup(&file[i]);
	if (!minishell->echo.out.file)
		return (0);
	minishell->echo.out.type = REDIR_OUT_APPEND;
	return (1);

}

int	heredoc_case(t_minishell *minishell, char *file)
{
	int	i;

	i = 2;
	if (file[i] == ' ')
		i++;
	minishell->echo.in.file = strdup(&file[i]);
	if (!minishell->echo.in.file)
		return (0);
	minishell->echo.in.type = HEREDOC;
	return (1);
}
