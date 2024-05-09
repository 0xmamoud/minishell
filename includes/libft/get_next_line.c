/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:07:40 by kane              #+#    #+#             */
/*   Updated: 2024/05/09 20:47:48 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <stdio.h>

char	*get_next_line(int fd, int clr)
{
	static t_lst	*lst;
	char			*line;

	if (fd < 0 || BUFFER_SIZE == 0)
		return (NULL);
	if (clr == 1)
	{
		ft_free_lst(lst);
		return (NULL);
	}
	line = NULL;
	ft_read_fd(fd, &lst);
	if (!lst)
		return (NULL);
	line = ft_getline(lst);
	ft_clean_lst(&lst);
	if (!*line)
	{
		ft_free_lst(lst);
		free(line);
		lst = NULL;
		return (NULL);
	}
	return (line);
}

void	ft_read_fd(int fd, t_lst **lst)
{
	char	*buf;
	int		read_bytes;

	read_bytes = 1;
	while (read_bytes != 0 && !ft_find_newline(*lst))
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buf)
			return ;
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes == -1 || (!buf && read_bytes == 0))
		{
			free(buf);
			ft_free_lst(*lst);
			*lst = NULL;
			return ;
		}
		buf[read_bytes] = '\0';
		ft_lstadd(lst, buf, read_bytes);
		free(buf);
	}
}

void	ft_lstadd(t_lst **lst, char *buf, int read_bytes)
{
	t_lst	*new;
	t_lst	*last;
	int		i;

	new = malloc(sizeof(t_lst));
	if (!new)
		return ;
	new->next = NULL;
	new->content = (char *)malloc(sizeof(char) * (read_bytes + 1));
	if (!new->content)
		return ;
	i = 0;
	while (i < read_bytes && buf[i])
	{
		new->content[i] = buf[i];
		i++;
	}
	new->content[i] = '\0';
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast_list(*lst);
	last->next = new;
}

char	*ft_getline(t_lst *lst)
{
	int		i;
	int		j;
	char	*line;

	line = malloc(sizeof(char) * (ft_linesize(lst) + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (lst)
	{
		j = 0;
		while (lst->content[j])
		{
			if (lst->content[j] == '\n')
			{
				line[i++] = lst->content[j];
				line[i] = '\0';
				return (line);
			}
			line[i++] = lst->content[j++];
		}
		lst = lst->next;
	}
	line[i] = '\0';
	return (line);
}

void	ft_clean_lst(t_lst **lst)
{
	t_lst	*tmp;
	t_lst	*last;
	int		i;
	int		j;

	tmp = malloc(sizeof(t_lst));
	if (!tmp || !(*lst))
		return ;
	last = ft_lstlast_list(*lst);
	tmp ->next = NULL;
	i = 0;
	while (last -> content[i] && last -> content[i] != '\n')
		i++;
	if (last -> content[i] == '\n')
		i++;
	tmp -> content = malloc(sizeof(char)
			* (ft_strlen(last -> content) - i + 1));
	if (!tmp -> content)
		return ;
	j = 0;
	while (last -> content[i])
		tmp -> content[j++] = last -> content[i++];
	tmp -> content[j] = '\0';
	ft_free_lst(*lst);
	*lst = tmp;
}

// int main()
// {
// 	int fd = open("./test.txt", O_RDONLY);
// 	int i = 0;
// 	while (i < 300)
// 	{
// 		char *line = get_next_line(fd);
// 		if (!line)
// 			return (0) ;
// 		printf("%s", line);
// 		free(line);
// 		i++;
// 	}
// }
