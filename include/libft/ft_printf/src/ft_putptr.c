/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kane <kane@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 23:00:00 by mkane             #+#    #+#             */
/*   Updated: 2023/11/21 15:19:45 by kane             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_putptr(void *ptr)
{
	int	strlen;

	strlen = 0;
	if (!ptr)
	{
		strlen += ft_putstr("(nil)");
		return (strlen);
	}
	strlen += ft_putstr("0x");
	strlen += ft_ptr_hex((unsigned long long)ptr, "0123456789abcdef");
	return (strlen);
}

int	ft_ptr_hex(unsigned long long nbr, char *base)
{
	int					strlen;
	unsigned long long	baselen;

	strlen = 0;
	baselen = ft_strlen(base);
	if (nbr < baselen)
		strlen += ft_putchar(base[nbr]);
	else
	{
		strlen += ft_ptr_hex((nbr / baselen), base);
		strlen += ft_ptr_hex((nbr % baselen), base);
	}
	return (strlen);
}
