/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 00:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/24 22:32:30 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals/signals.h"

static int	init_check(int argc, char **argv, t_head **env_gc)
{
	if (argc != 1)
	{
		printf("Usage: %s\n", argv[0]);
		return (1);
	}
	*env_gc = intializehead();
	if (!*env_gc)
	{
		printf("minishell: initialization failed\n");
		return (1);
	}
	return (0);
}

static void	main_loop(t_shell *shell, char **envp)
{
	char	*str;

	while (1)
	{
		str = readline("minishell$ ");
		handle_signal_after_readline(shell);
		if (!str)
		{
			printf("exit\n");
			break ;
		}
		if (str[0] && whitespacecheck(str))
		{
			add_history(str);
			startminishell(str, shell, envp);
		}
		free(str);
		if (shell->should_exit)
			break ;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	t_head	*env_gc;

	(void)argv;
	env_gc = NULL;
	if (init_check(argc, argv, &env_gc))
	{
		if (env_gc)
			gcallfree(env_gc);
		return (1);
	}
	if (init_shell(&shell, envp, env_gc))
	{
		printf("minishell: initialization failed\n");
		gcallfree(env_gc);
		return (1);
	}
	setupinteractive();
	main_loop(&shell, envp);
	rl_clear_history();
	gcallfree(env_gc);
	return (shell.exit_status);
}
