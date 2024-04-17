/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:37:49 by tbarret           #+#    #+#             */
/*   Updated: 2024/04/16 22:02:34 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_minishell minishell;
	
	minishell.env = NULL;
	char *str = "Bonjour \"$USER\" \"$USER\"\", 'comment vas-tu ?'\", \"$HOME\", '$USER'   $USER \'\'";
	ft_printf("str = %s\n", str);

	ft_printf("====================\n");

	if (!create_env(envp, &minishell))
	{
		printf("Error\n");
		return (1);
	}
	char *test = washer(str, &minishell);
	if (!test)
	{
		printf("Error\n");
		return (1);
	}
	printf("%s\n", test);
	printf("====================\n");
	free(test);
	env_lstclear(&minishell.env);
	return (0);
}
