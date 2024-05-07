/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 22:45:16 by mkane             #+#    #+#             */
/*   Updated: 2024/05/07 20:49:53 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_putnbr_base(int n, char *base)
{
	int			strlen;
	int			baselen;
	long int	nbr;

	strlen = 0;
	nbr = n;
	baselen = ft_strlen(base);
	if (nbr == -2147483648)
	{
		strlen += ft_putstr("-2147483648");
	}
	else if (nbr < 0)
	{
		strlen += ft_putchar('-');
		strlen += ft_putnbr_base(-nbr, base);
	}
	else if (nbr >= 0 && nbr < baselen)
		strlen += ft_putchar(base[nbr]);
	else
	{
		strlen += ft_putnbr_base((nbr / baselen), base);
		strlen += ft_putnbr_base((nbr % baselen), base);
	}
	return (strlen);
}
