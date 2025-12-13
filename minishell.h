/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 10:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/13 19:54:38 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "tokenization/tokenization.h"
# include "builtins/ft_utils.h"

/*
** Main shell structure - holds all shell state
*/
typedef struct s_shell
{
	char	**env;			/* Personal copy of environment */
	char	*pwd;			/* Current working directory */
	char	*oldpwd;		/* Previous working directory */
	int		exit_status;	/* Last command exit status ($?) */
	int		should_exit;	/* Flag to exit main loop */
}	t_shell;

/*
** Environment management
*/
char	**copy_environment(char **envp, t_head *gc);
char	*get_env_value(char **env, const char *key);
char	**set_env_value(char **env, const char *key, const char *value,
			t_head *gc);
char	**unset_env_value(char **env, const char *key);
int		env_array_size(char **env);

/*
** Built-ins
*/
int		builtin_pwd(void);
void	builtin_echo(char *str);
int		builtin_env(t_shell *shell);
int		builtin_cd(t_shell *shell, char *path);
int		builtin_export(t_shell *shell, char *str);
int		builtin_unset(t_shell *shell, char *str);
int		builtin_exit(t_shell *shell, char *args);

/*
** Signal handling
*/
void	setup_signals(void);
void	handle_sigint(int sig);

/*
** Execution
*/
int		is_builtin(const char *cmd);
int		execute_builtin(t_shell *shell, char *cmd, char *args);

#endif
