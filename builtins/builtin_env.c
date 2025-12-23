/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 20:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/23 13:37:27 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../utils/ft_utils.h"
#include <sys/wait.h>

char	*find_in_path(char *cmd, char **env);

static int	print_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		printf("%s\n", shell->env[i]);
		i++;
	}
	return (0);
}

static int	execute_cmd(char *cmd_path, char **args, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		execve(cmd_path, &args[1], shell->env);
		fprintf(stderr, "env: %s: No such file or directory\n", args[1]);
		exit(127);
	}
	if (cmd_path != args[1])
		free(cmd_path);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	builtin_env(t_shell *shell, char **args)
{
	char	*cmd_path;

	if (!args || !args[1])
		return (print_env(shell));
	cmd_path = find_in_path(args[1], shell->env);
	if (!cmd_path)
	{
		fprintf(stderr, "env: %s: No such file or directory\n", args[1]);
		return (127);
	}
	return (execute_cmd(cmd_path, args, shell));
}
