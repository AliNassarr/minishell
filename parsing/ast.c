/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 21:40:19 by invader           #+#    #+#             */
/*   Updated: 2025/12/25 01:13:17 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_treenode	*intializenode(t_parse_token *tokens, int count, t_head *head)
{
	t_treenode	*node;

	node = gcmalloc(head, sizeof(t_treenode));
	if (!node)
		return (NULL);
	node->tokens = tokens;
	node->token_count = count;
	node->heredoc_fd = -1;
	node->heredoc_no_expand = 0;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_treenode	*createast(t_parse_token *tokens, int count, t_head *head)
{
	t_treenode	*node;
	int			oppos;
	int			left_count;
	int			right_count;

	if (count == 0)
		return (intializenode(NULL, 0, head));
	oppos = findpipeoperator(tokens, 0, count - 1);
	if (oppos != -1)
	{
		node = intializenode(&tokens[oppos], 1, head);
		if (!node)
			return (NULL);
		left_count = oppos;
		right_count = count - oppos - 1;
		node->left = createast(tokens, left_count, head);
		node->right = createast(&tokens[oppos + 1], right_count, head);
		return (node);
	}
	oppos = findrediroperator(tokens, 0, count - 1);
	if (oppos != -1)
		return (createredirast(tokens, count, oppos, head));
	return (intializenode(tokens, count, head));
}

t_treenode	*asthelper(char *str, t_head *head, char **pp)
{
	t_parse_token	*tokens;
	int				count;

	count = 0;
	tokens = parsingprep(str, &count, head, pp);
	if (!tokens)
		return (NULL);
	return (createast(tokens, count, head));
}
