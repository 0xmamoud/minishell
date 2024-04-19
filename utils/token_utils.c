/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:17:03 by mkane             #+#    #+#             */
/*   Updated: 2024/04/19 21:34:11 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_pipe(char *str)
{
	if (!str)
		return (0);
	if (ft_strncmp(str, "|", 1) == 0)
		return (1);
	return (0);
}

int	is_redirection(char *str)
{
	if (!str)
		return (0);
	if (str[0] == '>' && str[1] == '>')
		return (1);
	if (str[0] == '>' && str[1] != '>')
		return (1);
	if (str[0] == '<' && str[1] != '<')
		return (1);
	if (str[0] == '<' && str[1] == '<')
		return (1);
	return (0);
}
