/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:50:33 by tbarret           #+#    #+#             */
/*   Updated: 2024/04/24 14:56:35 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void control_c(int signal)
{
	(void)signal;
	ft_putstr_fd("\nminishell> ", 1);
}

static void control_slash(int signal)
{
	(void)signal;
}

void interactive_mode(void)
{
	signal(SIGINT, &control_c);
	signal(SIGQUIT, &control_slash);
}