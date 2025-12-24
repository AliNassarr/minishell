/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 04:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/24 03:16:33 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"
#include "../utils/ft_utils.h"

static int	handle_output_redir(t_treenode *node, t_shell *shell,
		t_head *head, t_token_type type)
{
	int	fd;
	int	saved_fd;
	int	exit_status;

	if (type == REDIR_OUT)
		fd = open(node->right->tokens[0].str,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(node->right->tokens[0].str,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (perror("minishell"), 1);
	saved_fd = dup(STDOUT_FILENO);
	if (saved_fd == -1)
		return (close(fd), perror("minishell: dup"), 1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	fflush(stdout);
	exit_status = execute_ast(node->left, shell, head);
	fflush(stdout);
	dup2(saved_fd, STDOUT_FILENO);
	close(saved_fd);
	return (exit_status);
}

static int	handle_input_redir(t_treenode *node, t_shell *shell, t_head *head)
{
	int	fd;
	int	saved_fd;
	int	exit_status;

	fd = open(node->right->tokens[0].str, O_RDONLY);
	if (fd == -1)
		return (perror("minishell"), 1);
	saved_fd = dup(STDIN_FILENO);
	if (saved_fd == -1)
		return (close(fd), perror("minishell: dup"), 1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	exit_status = execute_ast(node->left, shell, head);
	dup2(saved_fd, STDIN_FILENO);
	close(saved_fd);
	return (exit_status);
}

static int	handle_heredoc(t_treenode *node, t_shell *shell, t_head *head)
{
	int		saved_fd;
	int		exit_status;

	if (node->heredoc_fd < 0)
	{
		write(2, "minishell: heredoc error\n", 25);
		return (1);
	}
	saved_fd = dup(STDIN_FILENO);
	if (saved_fd == -1)
	{
		close(node->heredoc_fd);
		perror("minishell: dup");
		return (1);
	}
	dup2(node->heredoc_fd, STDIN_FILENO);
	close(node->heredoc_fd);
	exit_status = execute_ast(node->left, shell, head);
	dup2(saved_fd, STDIN_FILENO);
	close(saved_fd);
	return (exit_status);
}

int	handle_redirection(t_treenode *node, t_shell *shell, t_head *head)
{
	t_token_type	type;

	if (!node || !node->tokens)
		return (1);
	type = node->tokens[0].type;
	if (type == REDIR_OUT || type == REDIR_APPEND)
		return (handle_output_redir(node, shell, head, type));
	else if (type == REDIR_IN)
		return (handle_input_redir(node, shell, head));
	else if (type == HEREDOC)
		return (handle_heredoc(node, shell, head));
	return (1);
}
