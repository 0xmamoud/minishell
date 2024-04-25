/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:37:17 by mkane             #+#    #+#             */
/*   Updated: 2024/04/25 10:28:44 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd(t_minishell *minishell)
{
	char	*pwd;

	if (!redirection(minishell))
		return ;
	if (!init_files(minishell))
		return (free_and_close(minishell));
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (free_and_close(minishell));
	ft_printf("%s\n", pwd);
	ft_exit(minishell, 0, 0, 0);
	free(pwd);
	free_and_close(minishell);
}
