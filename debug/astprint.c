/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astprint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: invader <invader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 23:15:01 by invader           #+#    #+#             */
/*   Updated: 2025/12/19 23:17:22 by invader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	print_tokens(t_parse_token *tokens, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (i > 0)
			printf(" ");
		printf("%s", tokens[i].str);
		i++;
	}
}

void	print_ast_helper(t_treenode *node, int depth, char *prefix)
{
	int	i;

	if (!node)
		return ;
	i = 0;
	while (i < depth)
	{
		printf("    ");
		i++;
	}
	printf("%s", prefix);
	if (node->token_count == 1 && (node->tokens[0].type == PIPE
			|| node->tokens[0].type == OR || node->tokens[0].type == AND
			|| node->tokens[0].type == REDIR_IN || node->tokens[0].type == REDIR_OUT
			|| node->tokens[0].type == REDIR_APPEND || node->tokens[0].type == HEREDOC))
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

void	print_ast(t_treenode *root)
{
	if (!root)
	{
		printf("(empty tree)\n");
		return ;
	}
	printf("\n=== AST Structure ===\n");
	print_ast_helper(root, 0, "Root: ");
	printf("=====================\n\n");
}
