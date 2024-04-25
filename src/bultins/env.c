/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:02:34 by mkane             #+#    #+#             */
/*   Updated: 2024/04/25 18:21:14 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env(t_minishell *minishell)
{
	t_env	*tmp;

	if (!redirection(minishell))
		return ;
	if (!init_files(minishell))
		return (free_and_close(minishell));
	tmp = minishell->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->content, ""))
			ft_printf("%s\n", tmp->name);
		else
			ft_printf("%s=%s\n", tmp->name, tmp->content);
		tmp = tmp->next;
	}
	ft_exit(minishell, 0, 0, 0);
	free_and_close(minishell);
}
