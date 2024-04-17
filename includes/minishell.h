/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:14:51 by mkane             #+#    #+#             */
/*   Updated: 2024/04/17 13:39:21 by mkane            ###   ########.fr       */
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
# include "libft/libft.h"

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
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_tokenizer
{
	char				*cmd;
	t_token_type		type;
	struct s_tokenizer	*next;
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
}	t_pipe;

typedef struct s_minishell
{
	int			env_ignore;
	t_env		*env;
	t_pipe		pipe;
	t_cmd		*cmd;
}	t_minishell;

// parsing
char	*washer(char *str, t_minishell *minishell);

// utils
void	clear_tab(char **tab);
t_env	*env_lstnew(char *name, char *content);
t_env	*env_lstlast(t_env *env);
void	env_lstadd_back(t_env **env, t_env *new);
void	env_lstdelnode(t_env **env, char *name);
void	env_lstclear(t_env **env);
int		create_env(char **envp, t_minishell *minishell);
char	*find_env(t_env *env, char *name);

#endif