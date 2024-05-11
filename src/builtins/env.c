/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:02:34 by mkane             #+#    #+#             */
/*   Updated: 2024/05/01 21:30:30 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env(t_minishell *minishell)
{
	t_env	*tmp;

	tmp = minishell->env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->content, ""))
			printf("%s\n", tmp->name);
		else
			printf("%s=%s\n", tmp->name, tmp->content);
		tmp = tmp->next;
	}
	ft_exit(0, 0, 0);
}
