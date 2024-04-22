/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:15:19 by mkane             #+#    #+#             */
/*   Updated: 2024/04/22 18:16:47 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	export(t_minishell *minishell)
{
	t_token	*token;

	if (!redirection(minishell))
		return ;
	if (!init_files(minishell))
		return (free_and_close(minishell));
	token = minishell->token;
	while (token && token->type != COMMAND)
		token = token->next;
	if (token)
		token = token->next;
	if (!token)
		return (free_and_close(minishell));

}
