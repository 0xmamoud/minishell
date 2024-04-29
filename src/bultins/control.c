/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:50:33 by tbarret           #+#    #+#             */
/*   Updated: 2024/04/27 17:06:56 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void control_c_parent(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", -1);
	rl_redisplay();
	get_status(130, 0);
}

void control_c_child(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", 1);
	get_status(130, 0);
}


void control_back_slash_child(int signal)
{
	(void)signal;
	ft_putstr_fd("Quit\n", 1);
	get_status(131, 0);
}

void control_back_slash_parent(int signal)
{
	(void)signal;
	write(1, "\n", 2);
}