/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 20:18:25 by mkane             #+#    #+#             */
/*   Updated: 2023/11/13 18:30:54 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*destcpy;
	const char	*srccpy;

	destcpy = dest;
	srccpy = src;
	if (!n)
		return (dest);
	if (!dest && !src)
		return (NULL);
	while (n > 0)
	{
		*destcpy = *srccpy;
		n--;
		destcpy++;
		srccpy++;
	}
	return (dest);
}
