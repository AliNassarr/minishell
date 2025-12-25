/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 04:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/25 02:48:05 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"
#include <sys/wait.h>

static void	handle_pipe_child_left(int *pipefd, t_treenode *node,
		t_shell *shell, t_head *head)
{
	extern volatile sig_atomic_t	g_signal;

	g_signal &= ~0x100;
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	restoredefaults();
	exit(execute_ast(node->left, shell, head));
}

static void	handle_pipe_child_right(int *pipefd, t_treenode *node,
		t_shell *shell, t_head *head)
{
	extern volatile sig_atomic_t	g_signal;

	g_signal &= ~0x100;
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	restoredefaults();
	exit(execute_ast(node->right, shell, head));
}

static int	wait_and_get_status(pid_t pid1, pid_t pid2)
{
	int	status;
	int	status2;

	waitpid(pid1, &status, 0);
	waitpid(pid2, &status2, 0);
	if (WIFSIGNALED(status))
		return (checksignalstatus(status));
	return (checksignalstatus(status2));
}

int	execute_pipe(t_treenode *node, t_shell *shell, t_head *head)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	precreate_output_files(node->left);
	if (pipe(pipefd) == -1)
		return (perror("pipe"), 1);
	pid1 = fork();
	if (pid1 == -1)
		return (close(pipefd[0]), close(pipefd[1]), perror("fork"), 1);
	if (pid1 == 0)
		handle_pipe_child_left(pipefd, node, shell, head);
	pid2 = fork();
	if (pid2 == -1)
		return (close(pipefd[0]), close(pipefd[1]), perror("fork"), 1);
	if (pid2 == 0)
		handle_pipe_child_right(pipefd, node, shell, head);
	close(pipefd[0]);
	close(pipefd[1]);
	return (wait_and_get_status(pid1, pid2));
}
