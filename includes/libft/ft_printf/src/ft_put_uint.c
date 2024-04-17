/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_uint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kane <kane@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 00:31:02 by mkane             #+#    #+#             */
/*   Updated: 2023/11/21 14:12:18 by kane             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_put_uint(unsigned int nbr, char *base)
{
	int					strlen;
	unsigned int		baselen;

	strlen = 0;
	baselen = ft_strlen(base);
	if (nbr > baselen - 1)
	{
		strlen += ft_put_uint((nbr / baselen), base);
		strlen += ft_put_uint((nbr % baselen), base);
	}
	else
	{
		strlen += ft_putchar(base[nbr]);
	}
	return (strlen);
}
