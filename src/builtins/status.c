/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:19:42 by tbarret           #+#    #+#             */
/*   Updated: 2024/05/10 21:08:30 by mkane            ###   ########.fr       */
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
