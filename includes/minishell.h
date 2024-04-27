/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:14:51 by mkane             #+#    #+#             */
/*   Updated: 2024/04/27 17:45:41 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <signal.h>

typedef enum e_token_type
{
	COMMAND,
	PIPE,
	REDIRECTION,
	TOKEN_COUNT
}						t_token_type;

typedef enum e_type_redirection
{
	REDIR_OUT,
	REDIR_OUT_APPEND,
	REDIR_IN,
	HEREDOC
}						t_type_redirection;

typedef enum e_builtin
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	BUILTIN_COUNT
}						t_builtin;

typedef struct s_env
{
	char				*name;
	char				*content;
	struct s_env		*next;
}						t_env;

typedef struct s_token
{
	char				*cmd;
	t_token_type		type;
	struct s_token		*next;
}						t_token;

typedef struct s_redirection
{
	int					fd;
	int					saved_stdout;
	int					saved_stdin;
	t_type_redirection	type;
	char				*file;
}						t_redirection;
typedef struct s_cmd
{
	char				*cmd;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_echo
{
	int					option;
	char				*str;
	t_redirection		in;
	t_redirection		out;
}						t_echo;

typedef struct s_pipe
{
	pid_t				pid;
	int					fd[2];
	int					fd_in;
	int					fd_out;
	int					fd_append;
	int					here_doc;
	int					len_cmd;
	int					loop_index;
	int					start;
}						t_pipe;

typedef struct s_minishell
{
	int					env_ignore;
	char				*line;
	t_token				*token;
	t_builtin			builtin;
	t_env				*env;
	t_pipe				pipe;
	t_cmd				*cmd;
	t_redirection		in;
	t_redirection		out;
	t_echo				echo;
	int					status;
}						t_minishell;

// parsing
int						washer(t_minishell *minishell);
int						create_token(t_minishell *minishell, char *str);
void					expender(t_minishell *minishell);

// bultins
void					echo(t_minishell *minishell);
void					exit_minishell(t_minishell *minishell);
void					env(t_minishell *minishell);
void					unset(t_minishell *minishell);
void					export(t_minishell *minishell);
void					pwd(t_minishell *minishell);
void					cd(t_minishell *minishell);
void					minishell_execve(t_minishell *minishell);

// redirection
int						redirection(t_minishell *minishell);
int						init_files(t_minishell *minishell);

//file 

int						handle_files(t_minishell *minishell);
void					free_and_close(t_minishell *minishell);

//replace
int						count_replace(char *str, t_minishell *minishell);

//qhote.c

char	*find_and_replace(char *str, t_minishell *minishell);

//parse.c

void	parse(char *cmd, int ret, char c);
void	parse_redirection(char *cmd);

// utils
void					clear_tab(char **tab);
t_env					*env_lstnew(char *name, char *content);
t_env					*env_lstlast(t_env *env);
void					env_lstadd_back(t_env **env, t_env *new);
void					env_lstdelnode(t_env **env, char *name);
void					env_lstclear(t_env **env);
int						create_env(char **envp, t_minishell *minishell);
char					*find_env(t_env *env, char *name);

t_token					*token_lstnew(char *cmd, t_token_type type);
t_token					*token_lstlast(t_token *token);
void					token_lstadd_back(t_token **token, t_token *new);
void					token_lstclear(t_token **token);
int						is_pipe(char *str);
int						is_redirection(char *str);
int						cmd_len(t_minishell *minishell);
char					*ft_join(char *s1, char *s2);
char					**convert_env(t_env *env);
int						ft_strcmp(const char *s1, const char *s2);

t_cmd					*cmd_lstnew(char *cmd);
t_cmd					*cmd_lstlast(t_cmd *cmd);
void					cmd_lstadd_back(t_cmd **cmd, t_cmd *new);
void					cmd_lstclear(t_cmd **cmd);

// control
void					control_c_parent(int signal);
void					control_c_child(int signal);
void					control_back_slash_child(int signal);
void					control_back_slash_parent(int signal);
int						ft_exit(int status, int r, int e);
int						get_status(int status, int get);

//heredoc

void	ft_here_doc(char **delimiter);

#endif