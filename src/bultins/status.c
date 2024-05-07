/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:19:42 by tbarret           #+#    #+#             */
/*   Updated: 2024/05/07 17:47:51 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exit(int status, int r, int e)
{
	// printf("status = %d\n", status);
	// printf("r = %d\n", r);
	// printf("e = %d\n", e);
	get_status(status, 0);
	if (e)
		exit(status);
	return (r);
}

int	get_status(int status, int get)
{
	static int	save_status;
	int			ret;

	if (get == 3)
		return (save_status);
	if (get)
	{
		ret = save_status;
		save_status = status;
		return (ret);
	}
	save_status = status;
	return (save_status);
}
