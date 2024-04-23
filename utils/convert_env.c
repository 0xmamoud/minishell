/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 22:15:48 by mkane             #+#    #+#             */
/*   Updated: 2024/04/23 22:17:21 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	len_env(t_env *env)
{
	t_env	*tmp;
	int		i;

	tmp = env;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**convert_env(t_env *env)
{
	t_env	*tmp;
	char	**envp;
	char	*tmp_str;
	int		i;

	tmp = env;
	envp = (char **)malloc(sizeof(char *) * (len_env(env) + 1));
	if (!envp)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp)
	{
		tmp_str = ft_join(tmp->name, "=");
		if (!tmp_str)
			return (clear_tab(envp), free(tmp_str), NULL);
		envp[i] = ft_join(tmp_str, tmp->content);
		if (!envp[i])
			return (clear_tab(envp), free(tmp_str), NULL);
		i++;
		free(tmp_str);
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}
