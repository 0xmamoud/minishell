/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:19:42 by tbarret           #+#    #+#             */
/*   Updated: 2024/04/27 19:36:55 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exit(int status, int r, int e)
{
	get_status(status, 0);
	if (e)
		exit(status);
	return (r);
}

int	get_status(int status, int get)
{
	static int	save_status;
	int			ret;

	if (get)
	{
		ret = save_status;
		save_status = status;
		return (ret);
	}
	save_status = status;
	return (save_status);
}
