/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:37:17 by mkane             #+#    #+#             */
/*   Updated: 2024/04/27 17:10:22 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd(t_minishell *minishell)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (free_and_close(minishell));
	ft_printf("%s\n", pwd);
	ft_exit(0, 0, 0);
	free(pwd);
	free_and_close(minishell);
}
