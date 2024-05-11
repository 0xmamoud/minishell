/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:37:49 by tbarret           #+#    #+#             */
/*   Updated: 2024/05/11 19:58:37 by tbarret          ###   ########.fr       */
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
	minishell->line = NULL;
	minishell->status = 0;
	minishell->pipe.cmds = NULL;
	if (!create_env(envp, minishell))
	{
		ft_putstr_fd("Error: failed to create env\n", 2);
		exit(1);
	}
}

static void	reading(t_minishell *minishell)
{
	if (ft_strlen(minishell->line) == 0)
	{
		free(minishell->line);
		return ;
	}
	add_history(minishell->line);
	if (!washer(minishell))
	{
		printf("Error: failed to create token\n");
		ft_exit(1, 0, 0);
		free(minishell->line);
		return ;
	}
	if (!create_token(minishell, minishell->line))
	{
		printf("Error: failed to create token\n");
		free(minishell->line);
		return ;
	}
	expender(minishell);
	token_lstclear(&minishell->token);
	cmd_lstclear(&minishell->cmd);
	pipe_lstclear(&minishell->pipe.cmds);
	if (minishell->line)
		free(minishell->line);
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	minishell;

	init(ac, av, &minishell, envp);
	get_status(0, 0);
	signal(SIGINT, control_c_parent);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		minishell.line = readline("minishell> ");
		if (!minishell.line)
			break ;
		if (minishell.line[0] == EOF)
		{
			free(minishell.line);
			break ;
		}
		reading(&minishell);
	}
	rl_clear_history();
	env_lstclear(&minishell.env);
	return (0);
}
