/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 22:10:09 by mkane             #+#    #+#             */
/*   Updated: 2024/04/16 13:52:12 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	lens1;
	size_t	lens2;
	char	*str;

	str = NULL;
	lens1 = ft_strlen((const char *)s1);
	lens2 = ft_strlen((const char *)s2);
	str = (char *) ft_calloc((lens1 + lens2 + 1), sizeof(char));
	if (!str)
		return (NULL);
	if (!s1 && !s2)
	{
		*str = '\0';
		return (str);
	}
	ft_strlcpy(str, (const char *)s1, lens1 + 1);
	ft_strlcat(str, (const char *)s2, (lens1 + lens2 + 1));
	free(s1);
	return (str);
}