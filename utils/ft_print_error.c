/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 23:49:34 by mkane             #+#    #+#             */
/*   Updated: 2024/05/05 00:21:37 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_error(char *cmd, char *name, char *str)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, name, ft_strlen(name));
	write(2, ": ", 2);
	write(2, str, ft_strlen(str));
}
