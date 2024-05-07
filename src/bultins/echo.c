/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:00:32 by mkane             #+#    #+#             */
/*   Updated: 2024/05/07 20:49:53 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_string(t_cmd *cmd);
static int	find_option(char *str, t_minishell *minishell);

void	echo(t_minishell *minishell)
{
	char	*str;
	t_cmd	*cmd;

	cmd = minishell->cmd;
	cmd = cmd->next;
	minishell->echo.option = 0;
	while (cmd && find_option(cmd->cmd, minishell))
		cmd = cmd->next;
	str = get_string(cmd);
	if (!str)
	{
		ft_exit(0, 0, 0);
		return ;
	}
	printf("%s", str);
	if (!minishell->echo.option)
		printf("\n");
	free(str);
	ft_exit(0, 0, 0);
}

static int	find_option(char *str, t_minishell *minishell)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	minishell->echo.option = 1;
	return (1);
}

static char	*get_string(t_cmd *cmd)
{
	char	*str;
	t_cmd	*tmp;

	tmp = cmd;
	str = ft_strdup("");
	if (!str)
		return (NULL);
	while (tmp)
	{
		str = ft_strjoin(str, tmp->cmd);
		if (!str)
			return (NULL);
		tmp = tmp->next;
		if (tmp)
		{
			str = ft_strjoin(str, " ");
			if (!str)
				return (NULL);
		}
	}
	return (str);
}
