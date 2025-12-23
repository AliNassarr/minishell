/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astprint_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 00:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/23 03:35:41 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	print_tokens(t_parse_token *tokens, int count);

static void	print_indent(int depth)
{
	int	i;

	i = 0;
	while (i < depth)
	{
		printf("  ");
		i++;
	}
}

void	print_ast_helper(t_treenode *node, int depth, char *prefix)
{
	if (!node)
		return ;
	print_indent(depth);
	printf("%s", prefix);
	if (node->token_count == 1 && (node->tokens[0].type == PIPE
			|| node->tokens[0].type == OR || node->tokens[0].type == AND
			|| node->tokens[0].type == REDIR_IN
			|| node->tokens[0].type == REDIR_OUT
			|| node->tokens[0].type == REDIR_APPEND
			|| node->tokens[0].type == HEREDOC))
	{
		printf("[OP: %s]\n", node->tokens[0].str);
	}
	else
	{
		printf("[");
		print_tokens(node->tokens, node->token_count);
		printf("]\n");
	}
	if (node->left)
		print_ast_helper(node->left, depth + 1, "L: ");
	if (node->right)
		print_ast_helper(node->right, depth + 1, "R: ");
}
