/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:14:51 by mkane             #+#    #+#             */
/*   Updated: 2024/05/13 21:39:43 by mkane            ###   ########.fr       */
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
# include <errno.h>
# include <dirent.h>

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

typedef struct s_pipe_cmds
{
	char				*cmd;
	t_builtin			type;
	int					index;
	t_redirection		in;
	t_redirection		out;
	struct s_pipe_cmds	*next;
}						t_pipe_cmds;

typedef struct s_pipe
{
	pid_t				*pid;
	int					len_pid;
	int					fd[2];
	int					prev_fd;
	t_pipe_cmds			*cmds;
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
void					pwd(void);
int						cd(t_minishell *minishell);
void					minishell_execve(t_minishell *minishell);
int						excecute(t_minishell *minishell);
char					*get_path(t_minishell *minishell, char *cmd);

// pipe
void					minishell_pipe(t_minishell *minishell);
int						pipe_process(t_minishell *minishell,
							t_pipe_cmds **cmds);
int						init_pipe(t_minishell *minishell);
int						pipe_redirection(t_minishell *minishell);
void					pipe_open_heredocs(t_minishell *minishell);
int						pipe_infile_redirection(t_pipe_cmds **cmds);
int						pipe_outfile_redirection(t_pipe_cmds **cmds);
int						sub_pipe_redirection(t_token *token,
							t_pipe_cmds **pipe);
int						pipe_types(t_minishell *minishell);

// redirection
int						redirection(t_minishell *minishell);
int						init_files(t_minishell *minishell);

//file 

int						handle_files(t_minishell *minishell);
void					free_and_close(t_minishell *minishell);

//replace
int						count_replace(char *str, t_minishell *minishell);

//qhote.c

char					*find_and_replace(char *str, t_minishell *minishell);

//parse.c

void					parse(char *cmd, int ret, char c);
void					parse_redirection(char *cmd);

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
int						cmd_lstsize(t_cmd *cmd);

t_pipe_cmds				*pipe_lstnew(char *cmd, int index);
t_pipe_cmds				*pipe_lstlast(t_pipe_cmds *pipe);
void					pipe_lstadd_back(t_pipe_cmds **pipe, t_pipe_cmds *new);
void					pipe_lstclear(t_pipe_cmds **pipe);

void					ft_print_error(char *cmd, char *str, char *str2);

// control
void					control_c_parent(int signal);
void					control_c_child(int signal);
void					control_c_heredoc(int signal);
void					control_back_slash_child(int signal);
void					control_back_slash_parent(int signal);
int						ft_exit(int status, int r, int e);
int						get_status(int status, int get);

//heredoc

void					ft_here_doc(char **delimiter, t_minishell *minishell);

//quote utils
int						is_operator(char c);
int						handle_dollars(char **split, t_minishell *minishell);
int						after_dollars(char a);
void					after_interrogation(char *str, char **tmp, int *j);
//env utils.c

char					*get_env_value(char *str, t_minishell *minishell,
							int *i);
void					append_env_value(char *new, char *tmp);

void					ft_heredoc_exit_free_minishell(t_minishell *minishell);
void					ft_heredoc_clear_file(t_minishell *minishell);
int						ft_open_heredoc_fd(char **delimiter, char *fd_name);
#endif