/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:15:19 by mkane             #+#    #+#             */
/*   Updated: 2024/04/27 00:24:01 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int		add_with_value(t_minishell *minishell, t_cmd *cmds);
static void		print_export(t_minishell *minishell);
static int		is_all_alpha(char *str);

void	export(t_minishell *minishell)
{
	t_env	*new;
	t_cmd	*cmds;

	cmds = minishell->cmd;
	cmds = cmds->next;
	if (!cmds)
		return (print_export(minishell), free_and_close(minishell));
	while (cmds)
	{
		if (!is_all_alpha(cmds->cmd))
		{
			ft_printf("export: `%s': not a valid identifier\n", cmds->cmd);
			ft_exit(minishell, 1, 0, 0);
			return (free_and_close(minishell));
		}
		env_lstdelnode(&minishell->env, cmds->cmd);
		if (ft_strchr(cmds->cmd, '='))
		{
			if (!add_with_value(minishell, cmds))
				return (free_and_close(minishell));
		}
		else
		{
			new = env_lstnew(cmds->cmd, "");
			if (!new)
				return (free_and_close(minishell));
			env_lstadd_back(&minishell->env, new);
		}
		cmds = cmds->next;
	}
	free_and_close(minishell);
}

static	int	is_all_alpha(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalpha(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	print_export(t_minishell *minishell)
{
	t_env	*tmp;

	tmp = minishell->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->content, "") == 0)
			ft_printf("declare -x %s\n", tmp->name);
		else
			ft_printf("declare -x %s=\"%s\"\n", tmp->name, tmp->content);
		tmp = tmp->next;
	}
}

static int	add_with_value(t_minishell *minishell, t_cmd *cmds)
{
	t_env	*new;
	char	**split;

	split = ft_split(cmds->cmd, '=');
	if (!split)
		return (0);
	new = env_lstnew(split[0], split[1]);
	if (!new)
		return (0);
	env_lstadd_back(&minishell->env, new);
	clear_tab(split);
	return (1);
}
