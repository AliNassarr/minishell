/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_simple.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 04:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/24 04:25:36 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"
#include <sys/wait.h>
#include <errno.h>

static int	execute_external_cmd(char **cmd_array, char **env, char *cmd_path,
		char *original_cmd)
{
	pid_t		pid;
	int			status;
	extern int	g_in_parent;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		g_in_parent = 0;
		restoredefaults();
		execve(cmd_path, cmd_array, env);
		if (errno == EACCES || errno == EISDIR)
		{
			perror("minishell");
			exit(126);
		}
		perror("minishell");
		exit(127);
	}
	waitpid(pid, &status, 0);
	if (cmd_path != original_cmd)
		free(cmd_path);
	return (checksignalstatus(status));
}

int	execute_simple_command(t_treenode *node, t_shell *shell, t_head *head)
{
	char	**cmd_array;
	char	*cmd_path;
	char	*original_cmd;

	if (!node || !node->tokens || node->token_count == 0)
		return (0);
	cmd_array = extract_command(node->tokens, node->token_count, head);
	if (!cmd_array || !cmd_array[0])
		return (0);
	if (is_builtin(cmd_array[0]))
		return (execute_builtin(shell, cmd_array[0], cmd_array));
	original_cmd = cmd_array[0];
	cmd_path = find_command_path(cmd_array[0], shell->env);
	if (!cmd_path)
	{
		fprintf(stderr, "minishell: %s: command not found\n", original_cmd);
		return (127);
	}
	return (execute_external_cmd(cmd_array, shell->env, cmd_path,
			original_cmd));
}
