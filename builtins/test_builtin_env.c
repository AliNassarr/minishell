/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtin_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 20:20:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/13 23:09:15 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(void)
{
	t_shell	shell;
	t_head	gc;
	char	*test_env[] = {
		"HOME=/home/alnassar",
		"PATH=/usr/bin:/bin",
		"USER=alnassar",
		"SHELL=/bin/bash",
		NULL
	};

	gc.head = NULL;
	shell.env = copy_environment(test_env, &gc);
	shell.pwd = NULL;
	shell.oldpwd = NULL;
	shell.exit_status = 0;
	shell.should_exit = 0;
	printf("=== Testing builtin_env ===\n");
	builtin_env(&shell);
	printf("\n=== Test Complete ===\n");
	gc_free_all(&gc);
	return (0);
}
