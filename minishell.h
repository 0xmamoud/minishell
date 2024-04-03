/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:14:51 by mkane             #+#    #+#             */
/*   Updated: 2024/04/03 19:14:27 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>

typedef enum e_token_type
{
	COMMAND,
	SUBCOMMAND,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	REDIR_APPEND,
	END,
	STATUS
}	t_token_type;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_tokenizer
{
	char			*cmd;
	t_token_type	type;
}	t_tokenizer;

typedef struct s_cmd
{
	char			**cmd;
	char			*path;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_pipe
{
	pid_t	pid;
	int		fd[2];
	int		fd_in;
	int		fd_out;
	int		fd_append;
	int		here_doc;
	int		len_cmd;
	int		loop_index;
	int		start;
	t_cmd	*cmd;
}	t_pipe;

#endif