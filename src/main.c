/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:37:49 by tbarret           #+#    #+#             */
/*   Updated: 2024/04/19 18:32:08 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	init(int ac, char **av, t_minishell *minishell, char **envp)
{
	(void)ac;
	(void)av;
	minishell->env = NULL;
	minishell->cmd = NULL;
	minishell->token = NULL;
	if (!create_env(envp, minishell))
	{
		ft_putstr_fd("Error: failed to create env\n", 2);
		exit(1);
	}
}

int	main(int ac, char **av, char **envp)
{
	char		*line;
	t_minishell	minishell;
	t_token		*tmp;

	tmp = NULL;
	init(ac, av, &minishell, envp);
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		if (ft_strncmp(line, "exit", 4) == 0)
		{
			free(line);
			break ;
		}
		add_history(line);
		if (!washer(line))
		{
			printf("Error: failed to create token\n");
			free(line);
			continue ;
		}
		if (!create_token(&minishell, line))
		{
			printf("Error: failed to create token\n");
			free(line);
			continue ;
		}
		tmp = minishell.token;
		while (tmp)
		{
			printf("cmd = %s, token = %d\n", tmp->cmd, tmp->type);
			tmp = tmp->next;
		}
		token_lstclear(&minishell.token);
		free(line);
	}
	env_lstclear(&minishell.env);
	return (0);
}
