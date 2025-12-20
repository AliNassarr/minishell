/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 23:43:39 by invader           #+#    #+#             */
/*   Updated: 2025/12/20 21:37:17 by alnassar         ###   ########.fr       */
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

	shell->env = copy_environment(envp, env_gc);
	if (!shell->env)
		return (1);
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
	extern volatile sig_atomic_t	g_signal_flag;

	if (g_signal_flag == SIGINT)
	{
		shell->exit_status = 130;
		g_signal_flag = 0;
	}
}

/*
** startminishell - Parse and execute a command line
*/
void	startminishell(char *str, t_shell *shell, char **envp)
{
	char		*fixed;
	char		**pp;
	t_treenode	*node;
	t_head		*head;
	int			exit_status;

	head = intializehead();
	if (!head)
		return ;
	pp = envp;
	if (!quotecheck(str))
	{
		printf("minishell: syntax error: unclosed quotes\n");
		shell->exit_status = 2;
		return (gcallfree(head));
	}
	fixed = fixspaces(str, head, 0, 0);
	if (!fixed)
		return (gcallfree(head));
	node = asthelper(fixed, head, pp);
	if (!node)
	{
		shell->exit_status = 2;
		return (gcallfree(head));
	}
	print_ast(node);
	setupexecution();
	exit_status = execute_ast(node, shell, head);
	setupinteractive();
	shell->exit_status = exit_status;
	gcallfree(head);
}

/*
** main - Main entry point for minishell
** Initializes shell, sets up signals, and runs the REPL loop
*/
int	main(int argc, char **argv, char **envp)
{
	char		*str;
	t_shell		shell;
	t_head		*env_gc;

	(void)argv;
	if (argc != 1)
	{
		printf("Usage: %s\n", argv[0]);
		return (1);
	}
	env_gc = intializehead();
	if (!env_gc || init_shell(&shell, envp, env_gc))
	{
		printf("minishell: initialization failed\n");
		return (1);
	}
	setupinteractive();
	while (1)
	{
		str = readline("minishell$ ");
		handle_signal_after_readline(&shell);
		if (!str)
		{
			printf("exit\n");
			break ;
		}
		if (str[0] && whitespacecheck(str))
		{
			add_history(str);
			startminishell(str, &shell, envp);
		}
		free(str);
		if (shell.should_exit)
			break ;
	}
	rl_clear_history();
	gcallfree(env_gc);
	return (shell.exit_status);
}
