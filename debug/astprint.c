/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astprint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 23:15:01 by invader           #+#    #+#             */
/*   Updated: 2025/12/23 03:35:41 by alnassar         ###   ########.fr       */
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

void	print_ast_helper(t_treenode *node, int depth, char *prefix);

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
