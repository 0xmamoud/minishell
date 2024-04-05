/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:45:59 by kane              #+#    #+#             */
/*   Updated: 2023/11/13 18:31:19 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*destcpy;
	unsigned char		*srccpy;

	destcpy = (unsigned char *) dest;
	srccpy = (unsigned char *) src;
	if (!dest && !src)
		return (NULL);
	if (destcpy < srccpy)
		ft_memcpy(dest, src, n);
	else
	{
		while (n > 0)
		{
			n--;
			*(destcpy + n) = *(srccpy + n);
		}
	}
	return (dest);
}
