/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:09:40 by kane              #+#    #+#             */
/*   Updated: 2023/11/14 14:55:44 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (len == 0 && *little)
		return (NULL);
	if (!(*little))
		return ((char *)big);
	while (*(big + i) && i < len)
	{
		j = 0;
		while ((i + j) < len && *(big + i + j) == *(little + j))
		{
			j++;
			if (!*(little + j))
				return ((char *)(big + i));
		}
		i++;
	}
	return (NULL);
}
