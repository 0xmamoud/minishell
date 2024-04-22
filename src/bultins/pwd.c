/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:37:17 by mkane             #+#    #+#             */
/*   Updated: 2024/04/22 19:37:47 by mkane            ###   ########.fr       */
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
	free(pwd);
	free_and_close(minishell);
}
