/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 20:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/23 14:02:35 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

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
