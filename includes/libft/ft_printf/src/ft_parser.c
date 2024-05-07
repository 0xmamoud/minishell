/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 21:48:45 by mkane             #+#    #+#             */
/*   Updated: 2024/05/07 20:49:53 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_parser(va_list arg, const char c)
{
	int	strlen;

	strlen = 0;
	if (c == 'c')
		strlen += ft_putchar(va_arg(arg, int));
	else if (c == 's')
		strlen += ft_putstr(va_arg(arg, char *));
	else if (c == 'p')
		strlen += ft_putptr(va_arg(arg, void *));
	else if (c == 'd' || c == 'i')
		strlen += ft_putnbr_base(va_arg(arg, int), "0123456789");
	else if (c == 'u')
		strlen += ft_put_uint(va_arg(arg, unsigned int), "0123456789");
	else if (c == 'x')
		strlen += ft_put_uint(va_arg(arg, int), "0123456789abcdef");
	else if (c == 'X')
		strlen += ft_put_uint(va_arg(arg, int), "0123456789ABCDEF");
	else if (c == '%')
		strlen += ft_putchar('%');
	return (strlen);
}
