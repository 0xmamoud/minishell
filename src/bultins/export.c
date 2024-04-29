/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:15:19 by mkane             #+#    #+#             */
/*   Updated: 2024/04/27 19:36:11 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int		add_with_value(t_minishell *minishell, t_cmd *cmds);
static void		print_export(t_minishell *minishell);
static int		is_all_alpha(char *str);
static int		while_export(t_minishell *minishell, t_cmd *cmds, t_env *new);

void	export(t_minishell *minishell)
{
	t_env	*new;
	t_cmd	*cmds;

	cmds = minishell->cmd;
	cmds = cmds->next;
	new = NULL;
	if (!cmds)
		return (print_export(minishell), free_and_close(minishell));
	while (cmds)
	{
		if (!while_export(minishell, cmds, new))
			return ;
		cmds = cmds->next;
	}
	free_and_close(minishell);
}

static int	while_export(t_minishell *minishell, t_cmd *cmds, t_env *new)
{
	if (!is_all_alpha(cmds->cmd))
	{
		ft_printf("export: `%s': not a valid identifier\n", cmds->cmd);
		return (ft_exit(1, 0, 0), free_and_close(minishell), 0);
	}
	env_lstdelnode(&minishell->env, cmds->cmd);
	if (ft_strchr(cmds->cmd, '='))
	{
		if (!add_with_value(minishell, cmds))
			return (free_and_close(minishell), 0);
	}
	else
	{
		new = env_lstnew(cmds->cmd, "");
		if (!new)
			return (free_and_close(minishell), 0);
		env_lstadd_back(&minishell->env, new);
	}
	return (1);
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
