/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 23:43:39 by invader           #+#    #+#             */
/*   Updated: 2025/12/24 16:49:40 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals/signals.h"
#include "utils/ft_utils.h"
#include <unistd.h>

/*
** whitespacecheck - Check if string contains non-whitespace characters
** Returns: 1 if non-whitespace found, 0 otherwise
*/
int	whitespacecheck(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '\0')
		return (0);
	return (1);
}

/*
** init_shell - Initialize shell structure with environment and defaults
** Returns: 0 on success, 1 on failure
*/
int	init_shell(t_shell *shell, char **envp, t_head *env_gc)
{
	char	cwd[1024];

	shell->env_gc = env_gc;
	shell->env = copy_environment(envp, env_gc);
	if (!shell->env)
		return (1);
	increment_shlvl(&shell->env, env_gc);
	shell->personal_path = gcmalloc(env_gc, sizeof(char *) * 1);
	if (!shell->personal_path)
		return (1);
	shell->personal_path[0] = NULL;
	shell->exit_status = 0;
	shell->should_exit = 0;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		shell->pwd = ft_strdup_gc(cwd, env_gc);
		shell->oldpwd = NULL;
	}
	else
	{
		shell->pwd = NULL;
		shell->oldpwd = NULL;
	}
	return (0);
}

/*
** handle_signal_after_readline - Check and handle signals after readline
** Updates exit status if Ctrl+C was pressed
*/
void	handle_signal_after_readline(t_shell *shell)
{
	extern volatile sig_atomic_t	g_signal;

	if ((g_signal & 0xFF) == SIGINT)
	{
		shell->exit_status = 130;
		g_signal = (g_signal & 0x100);
	}
}

/*
** startminishell - Parse and execute a command line
*/
void	startminishell(char *str, t_shell *shell, char **envp);
