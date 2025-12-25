/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 00:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/24 18:43:40 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

static int	precreate_file(t_treenode *node, t_token_type type)
{
	int	fd;

	if (type == REDIR_OUT)
		fd = open(node->right->tokens[0].str,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(node->right->tokens[0].str,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (-1);
	close(fd);
	return (0);
}

int	precreate_output_files(t_treenode *node)
{
	int	result;

	if (!node)
		return (0);
	if (node->token_count == 1 && (node->tokens[0].type == REDIR_OUT
			|| node->tokens[0].type == REDIR_APPEND))
	{
		result = precreate_file(node, node->tokens[0].type);
		if (result == -1)
			return (-1);
	}
	result = precreate_output_files(node->left);
	if (result == -1)
		return (-1);
	return (precreate_output_files(node->right));
}
