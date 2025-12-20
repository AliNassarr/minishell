/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 20:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/20 21:37:19 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"
#include <sys/wait.h>
#include <string.h>

/*
** extract_command - Extract command and arguments from tokens
** Returns: Array of strings [cmd, arg1, arg2, ..., NULL]
*/
char	**extract_command(t_parse_token *tokens, int count, t_head *head)
{
	char	**cmd_array;
	int		i;
	int		j;

	cmd_array = gcmalloc(head, sizeof(char *) * (count + 1));
	if (!cmd_array)
		return (NULL);
	i = 0;
	j = 0;
	while (i < count)
	{
		if (tokens[i].type == CMD || tokens[i].type == ARG)
		{
			cmd_array[j] = tokens[i].str;
			j++;
		}
		i++;
	}
	cmd_array[j] = NULL;
	return (cmd_array);
}

/*
** find_command_path - Find full path of command
** Searches in PATH environment variable
*/
char	*find_command_path(char *cmd, char **env)
{
	char	*path_env;
	char	*path_copy;
	char	*dir;
	char	*full_path;
	int		i;

	if (!cmd || cmd[0] == '/' || cmd[0] == '.')
		return (cmd);
	i = 0;
	while (env && env[i])
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
		{
			path_env = env[i] + 5;
			break ;
		}
		i++;
	}
	if (!env || !env[i])
		return (cmd);
	path_copy = strdup(path_env);
	if (!path_copy)
		return (cmd);
	dir = strtok(path_copy, ":");
	while (dir)
	{
		full_path = malloc(strlen(dir) + strlen(cmd) + 2);
		if (full_path)
		{
			strcpy(full_path, dir);
			strcat(full_path, "/");
			strcat(full_path, cmd);
			if (access(full_path, X_OK) == 0)
			{
				free(path_copy);
				return (full_path);
			}
			free(full_path);
		}
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (cmd);
}

/*
** execute_simple_command - Execute a simple command (no operators)
** Returns: Exit status of the command
*/
int	execute_simple_command(t_treenode *node, t_shell *shell, t_head *head)
{
	char	**cmd_array;
	char	*cmd_path;
	char	*original_cmd;
	pid_t	pid;
	int		status;

	if (!node || !node->tokens || node->token_count == 0)
		return (0);
	cmd_array = extract_command(node->tokens, node->token_count, head);
	if (!cmd_array || !cmd_array[0])
		return (0);
	if (is_builtin(cmd_array[0]))
		return (execute_builtin(shell, cmd_array[0], cmd_array));
	original_cmd = cmd_array[0];
	cmd_path = find_command_path(cmd_array[0], shell->env);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		restoredefaults();
		execve(cmd_path, cmd_array, shell->env);
		perror("minishell");
		exit(127);
	}
	waitpid(pid, &status, 0);
	if (cmd_path != original_cmd)
		free(cmd_path);
	return (checksignalstatus(status));
}

/*
** handle_redirection - Handle redirection operators
** Returns: Exit status
*/
int	handle_redirection(t_treenode *node, t_shell *shell, t_head *head)
{
	int		fd;
	int		saved_fd;
	int		exit_status;
	t_token_type	type;

	if (!node || !node->tokens)
		return (1);
	type = node->tokens[0].type;
	if (type == REDIR_OUT || type == REDIR_APPEND)
	{
		if (type == REDIR_OUT)
			fd = open(node->right->tokens[0].str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(node->right->tokens[0].str, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return (perror("minishell"), 1);
		saved_fd = dup(STDOUT_FILENO);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		exit_status = execute_ast(node->left, shell, head);
		dup2(saved_fd, STDOUT_FILENO);
		close(saved_fd);
		return (exit_status);
	}
	else if (type == REDIR_IN)
	{
		fd = open(node->right->tokens[0].str, O_RDONLY);
		if (fd == -1)
			return (perror("minishell"), 1);
		saved_fd = dup(STDIN_FILENO);
		dup2(fd, STDIN_FILENO);
		close(fd);
		exit_status = execute_ast(node->left, shell, head);
		dup2(saved_fd, STDIN_FILENO);
		close(saved_fd);
		return (exit_status);
	}
	return (1);
}

/*
** execute_pipe - Handle pipe operator
** Returns: Exit status of the last command in the pipe
*/
int	execute_pipe(t_treenode *node, t_shell *shell, t_head *head)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	if (pipe(pipefd) == -1)
		return (perror("pipe"), 1);
	pid1 = fork();
	if (pid1 == -1)
		return (perror("fork"), 1);
	if (pid1 == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		exit(execute_ast(node->left, shell, head));
	}
	pid2 = fork();
	if (pid2 == -1)
		return (perror("fork"), 1);
	if (pid2 == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		exit(execute_ast(node->right, shell, head));
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	return (checksignalstatus(status));
}

/*
** execute_logical - Handle AND (&&) and OR (||) operators
** Returns: Exit status
*/
int	execute_logical(t_treenode *node, t_shell *shell, t_head *head)
{
	int	left_status;

	left_status = execute_ast(node->left, shell, head);
	if (node->tokens[0].type == AND)
	{
		if (left_status == 0)
			return (execute_ast(node->right, shell, head));
		return (left_status);
	}
	else if (node->tokens[0].type == OR)
	{
		if (left_status != 0)
			return (execute_ast(node->right, shell, head));
		return (left_status);
	}
	return (1);
}

/*
** execute_ast - Main executor function that traverses the AST
** Returns: Exit status of the executed command(s)
*/
int	execute_ast(t_treenode *node, t_shell *shell, t_head *head)
{
	if (!node)
		return (0);
	if (node->token_count == 1 && node->tokens[0].type == PIPE)
		return (execute_pipe(node, shell, head));
	if (node->token_count == 1 && (node->tokens[0].type == AND
			|| node->tokens[0].type == OR))
		return (execute_logical(node, shell, head));
	if (node->token_count == 1 && (node->tokens[0].type == REDIR_OUT
			|| node->tokens[0].type == REDIR_IN
			|| node->tokens[0].type == REDIR_APPEND
			|| node->tokens[0].type == HEREDOC))
		return (handle_redirection(node, shell, head));
	return (execute_simple_command(node, shell, head));
}
