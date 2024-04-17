/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:17:03 by mkane             #+#    #+#             */
/*   Updated: 2024/04/17 20:31:11 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_pipe(char *str)
{
	if (str[0] == '|')
		return (1);
	return (0);
}

int	is_redirin(char *str)
{
	if (str[0] == '<' && str[1] != '<')
		return (1);
	return (0);
}

int	is_redirout(char *str)
{
	if (str[0] == '>' && str[1] != '>')
		return (1);
	return (0);
}

int	is_heredoc(char *str)
{
	if (str[0] == '<' && str[1] == '<')
		return (1);
	return (0);
}

int	is_redirappend(char *str)
{
	if (str[0] == '>' && str[1] == '>')
		return (1);
	return (0);
}