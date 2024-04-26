/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:37:49 by tbarret           #+#    #+#             */
/*   Updated: 2024/04/26 23:26:02 by mkane            ###   ########.fr       */
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
	if (!create_env(envp, minishell))
	{
		ft_putstr_fd("Error: failed to create env\n", 2);
		exit(1);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	minishell;

	init(ac, av, &minishell, envp);
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
		if (ft_strlen(minishell.line) == 0)
		{
			free(minishell.line);
			continue ;
		}
		add_history(minishell.line);
		if (strcmp(minishell.line, "$?") == 0)
		{
			printf("%d\n", minishell.status);
			ft_exit(&minishell, 127, 0, 0);
			free(minishell.line);
			continue ;
		}
		if (!washer(&minishell))
		{
			printf("Error: failed to create token\n");
			free(minishell.line);
			continue ;
		}
		if (!create_token(&minishell, minishell.line))
		{
			printf("Error: failed to create token\n");
			free(minishell.line);
			continue ;
		}
		expender(&minishell);
		token_lstclear(&minishell.token);
		cmd_lstclear(&minishell.cmd);
		free(minishell.line);
	}
	env_lstclear(&minishell.env);
	return (0);
}
