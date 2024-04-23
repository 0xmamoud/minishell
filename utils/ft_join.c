/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:59:10 by mkane             #+#    #+#             */
/*   Updated: 2024/04/23 22:24:21 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_join(char *s1, char *s2)
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
	return (str);
}
