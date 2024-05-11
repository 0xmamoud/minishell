/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:15:19 by mkane             #+#    #+#             */
/*   Updated: 2024/05/08 18:45:49 by mkane            ###   ########.fr       */
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
		return (print_export(minishell));
	while (cmds)
	{
		if (!while_export(minishell, cmds, new))
			return ;
		cmds = cmds->next;
	}
}

static int	while_export(t_minishell *minishell, t_cmd *cmds, t_env *new)
{
	if (!is_all_alpha(cmds->cmd))
	{
		ft_print_error("export: ", cmds->cmd, "is not a valid identifier\n");
		return (get_status(1, 0), 0);
	}
	if (ft_strchr(cmds->cmd, '='))
	{
		if (!add_with_value(minishell, cmds))
			return (0);
	}
	else
	{
		new = env_lstnew(cmds->cmd, "");
		if (!new)
			return (0);
		env_lstadd_back(&minishell->env, new);
	}
	return (1);
}

static	int	is_all_alpha(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_')
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
	env_lstdelnode(&minishell->env, split[0]);
	if (!split[1])
		new = env_lstnew(split[0], "");
	else
		new = env_lstnew(split[0], split[1]);
	if (!new)
		return (0);
	env_lstadd_back(&minishell->env, new);
	clear_tab(split);
	return (1);
}
