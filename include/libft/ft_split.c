/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 21:50:53 by mkane             #+#    #+#             */
/*   Updated: 2024/04/05 13:52:22 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	countword(const char *s, char set)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		if (*s != set && (i == 0 || *(s - 1) == set))
			i++;
		s++;
	}
	return (i);
}

static size_t	countwordsize(const char *s, char set)
{
	size_t	i;

	i = 0;
	while (*s != set && *s)
	{
		i++;
		s++;
	}
	return (i);
}

static void	ft_copy(const char *s, char *dst, char set)
{
	size_t	i;

	i = 0;
	while (*(s + i) != set && *(s + i))
	{
		*(dst + i) = *(s + i);
		i++;
	}
	*(dst + i) = '\0';
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	next;
	size_t	wordsize;

	str = ft_calloc(countword(s, c) + 1, sizeof(char *));
	if (!str)
		return (NULL);
	next = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		wordsize = countwordsize(s, c);
		if (wordsize > 0)
		{
			*(str + next) = ft_calloc(wordsize + 1, sizeof(char));
			if (!*(str + next))
				return (NULL);
			ft_copy(s, *(str + next), c);
			s += wordsize;
			next++;
		}
	}
	*(str + next) = 0;
	return (str);
}
