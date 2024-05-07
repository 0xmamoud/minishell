/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:02:42 by mkane             #+#    #+#             */
/*   Updated: 2024/05/07 20:49:53 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	exit_minishell(t_minishell *minishell)
{
	int	i;
	int status;

	ft_printf("exit\n");
	i = cmd_lstsize(minishell->cmd);
	status = 0;
	if (i > 2)
	{
		ft_putstr_fd("mini: exit: too many arguments\n", 2);
		ft_exit(1, 0, 0);
		return ;
	}
	if (i == 2 && !is_number(minishell->cmd->next->cmd))
	{
		ft_putstr_fd("mini: exit: ", 2);
		ft_putstr_fd(minishell->cmd->next->cmd, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		ft_exit(2, 0, 0);
		return ;
	}
	if (i == 2)
		status = ft_atoi(minishell->cmd->next->cmd);
	// printf("i: %d\n", i);
	free(minishell->line);
	token_lstclear(&minishell->token);
	cmd_lstclear(&minishell->cmd);
	free_and_close(minishell);
	pipe_lstclear(&minishell->pipe.cmds);
	env_lstclear(&minishell->env);
	// printf("EXIT CODE: %d\n", status);
	ft_exit(status, 0, 1);
}
