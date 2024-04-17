/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:37:49 by tbarret           #+#    #+#             */
/*   Updated: 2024/04/17 14:27:06 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_minishell	minishell;
	char		*str;
	char		*test;

	(void)ac;
	(void)av;
	minishell.env = NULL;
	str = "Bonjour \"$USER\" \"$USER\"\", 'comment vas-tu ?'\", \"$HOME\" '$USER'   $USER \'\'";
	ft_printf("str = %s\n", str);
	ft_printf("====================\n");
	if (!create_env(envp, &minishell))
	{
		printf("Error\n");
		return (1);
	}
	test = washer(str, &minishell);
	if (!test)
		return (printf("Error: env variable not found\n"), 1);
	printf("%s\n", test);
	printf("====================\n");
	free(test);
	env_lstclear(&minishell.env);
	return (0);
}
