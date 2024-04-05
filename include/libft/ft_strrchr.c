/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:39:16 by kane              #+#    #+#             */
/*   Updated: 2023/11/14 14:02:34 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*acc;

	acc = NULL;
	while (*s)
	{
		if (*s == (const char)c)
			acc = (char *)s;
		s++;
	}
	if (!c)
		return ((char *) s);
	return (acc);
}
