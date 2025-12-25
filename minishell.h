/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 23:44:12 by invader           #+#    #+#             */
/*   Updated: 2025/12/25 01:13:17 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include "utils/ft_utils.h"

typedef struct s_node
{
	void			*data;
	struct s_node	*next;
}	t_node;

typedef struct s_head
{
	t_node	*head;
}	t_head;

typedef enum e_token_type
{
	PIPE,
	OR,
	AND,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
	CMD,
	ARG,
	FILENAME,
	LIMITER,
	UNKNOWN
}	t_token_type;

typedef struct s_parse_token
{
	char			*str;
	t_token_type	type;
	int				was_quoted;
}	t_parse_token;

typedef struct s_treenode
{
	t_parse_token		*tokens;
	int					token_count;
	int					heredoc_fd;
	int					heredoc_no_expand;
	struct s_treenode	*left;
	struct s_treenode	*right;
}	t_treenode;

typedef struct s_shell
{
	char	**env;
	char	**personal_path;
	char	*pwd;
	char	*oldpwd;
	int		exit_status;
	int		should_exit;
	t_head	*env_gc;
}	t_shell;

/*
** Global variables
*/

char		*fixspaces(char *str, t_head *head, int i, int j);
int			quotecheck(char *str);
t_treenode	*asthelper(char *str, t_head *head, char **pp);
void		print_ast(t_treenode *root);
t_head		*intializehead(void);
void		gcallfree(t_head *head);
void		*gcmalloc(t_head *head, int size);

/*
** Environment management
*/
char		**copy_environment(char **envp, t_head *gc);
void		increment_shlvl(char ***env, t_head *gc);
char		*get_env_value(char **env, const char *key);
char		**set_env_value(char **env, const char *key, const char *value,
				t_head *gc);
char		**unset_env_value(char **env, const char *key, t_head *gc);
int			env_array_size(char **env);

/*
** Built-ins
*/
int			builtin_pwd(char *args);
void		builtin_echo(char *str);
int			builtin_env(t_shell *shell, char **args);
int			builtin_cd(t_shell *shell, char *path, t_head *gc);
int			builtin_export(t_shell *shell, char *str, t_head *gc);
int			builtin_unset(t_shell *shell, char *str, t_head *gc);
int			builtin_exit(t_shell *shell, char *args);

/*
** Signal handling
*/
void		setupinteractive(void);
void		setupexecution(void);
void		restoredefaults(void);
void		interactivehandler(int sig);
int			checksignalstatus(int status);
void		printsignalmsg(int signal_num);

/*
** Execution
*/
int			is_builtin(const char *cmd);
int			execute_builtin(t_shell *shell, char *cmd, char **args);
int			execute_ast(t_treenode *node, t_shell *shell, t_head *head);
int			dispatch_builtin(t_shell *shell, char *cmd, char **args,
				char *joined);

/*
** Main helpers
*/
int			whitespacecheck(char *str);
int			init_shell(t_shell *shell, char **envp, t_head *env_gc);
void		handle_signal_after_readline(t_shell *shell);
void		startminishell(char *str, t_shell *shell, char **envp);

#endif