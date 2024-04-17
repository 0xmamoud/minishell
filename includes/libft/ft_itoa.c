/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:14:58 by mkane             #+#    #+#             */
/*   Updated: 2023/11/15 20:38:20 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count(long int number)
{
	size_t	i;

	i = 1;
	while (number / 10)
	{
		number /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long int	number;
	size_t		len;
	char		*str;

	number = n;
	len = ft_count(n);
	if (n < 0)
	{
		number *= -1;
		len++;
	}
	str = ft_calloc((len + 1), sizeof(char));
	if (!str)
		return (NULL);
	*(str + len) = '\0';
	while (len > 0)
	{
		len--;
		*(str + len) = number % 10 + '0';
		number /= 10;
	}
	if (n < 0)
		*(str + 0) = '-';
	return (str);
}
