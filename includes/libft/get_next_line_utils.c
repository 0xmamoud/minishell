/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:22:39 by kane              #+#    #+#             */
/*   Updated: 2024/05/07 20:49:53 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

int	ft_find_newline(t_lst *lst)
{
	int		i;
	t_lst	*tmp;

	i = 0;
	if (!lst)
		return (0);
	tmp = ft_lstlast_list(lst);
	while (tmp -> content[i])
	{
		if (tmp -> content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_linesize(t_lst *lst)
{
	int	i;
	int	j;

	i = 0;
	while (lst)
	{
		j = 0;
		while (lst->content[j])
		{
			if (lst->content[j] == '\n')
				return (i + 1);
			j++;
			i++;
		}
		lst = lst->next;
	}
	return (i);
}

void	ft_free_lst(t_lst *lst)
{
	t_lst	*tmp;
	t_lst	*next;

	if (!(lst))
		return ;
	tmp = lst;
	while (tmp)
	{
		free(tmp -> content);
		next = tmp -> next;
		free(tmp);
		tmp = next;
	}
}

t_lst	*ft_lstlast_list(t_lst *lst)
{
	if (!lst)
		return (NULL);
	while (lst && lst -> next)
		lst = lst -> next;
	return (lst);
}
