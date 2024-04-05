/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 21:46:35 by kane              #+#    #+#             */
/*   Updated: 2023/11/13 17:30:38 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	srclen;
	size_t	dstlen;
	size_t	i;

	srclen = ft_strlen(src);
	i = 0;
	if (!size)
		return (srclen);
	dstlen = ft_strlen(dst);
	if (size < dstlen)
		return (srclen + size);
	while (i + dstlen < (size - 1) && *(src + i))
	{
		*(dst + i + dstlen) = *(src + i);
		i++;
	}
	*(dst + i + dstlen) = '\0';
	return (srclen + dstlen);
}
