/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 00:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/25 01:13:17 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	count_left_tokens(int count, int redir_pos)
{
	int	left_count;
	int	i;

	left_count = 0;
	i = 0;
	while (i < count)
	{
		if (i != redir_pos && i != redir_pos + 1)
			left_count++;
		i++;
	}
	return (left_count);
}

static t_parse_token	*copy_left_tokens(t_parse_token *tokens, int count,
		int redir_pos, t_head *head)
{
	t_parse_token	*left_tokens;
	int				left_count;
	int				i;
	int				j;

	left_count = count_left_tokens(count, redir_pos);
	left_tokens = gcmalloc(head, sizeof(t_parse_token) * left_count);
	if (!left_tokens)
		return (NULL);
	i = 0;
	j = 0;
	while (i < count)
	{
		if (i != redir_pos && i != redir_pos + 1)
			left_tokens[j++] = tokens[i];
		i++;
	}
	return (left_tokens);
}

t_treenode	*createredirast(t_parse_token *tokens, int count, int redir_pos,
		t_head *head)
{
	t_treenode		*node;
	t_parse_token	*left_tokens;
	int				left_count;

	node = intializenode(&tokens[redir_pos], 1, head);
	if (!node)
		return (NULL);
	if (tokens[redir_pos].type == HEREDOC && redir_pos + 1 < count)
	{
		if (tokens[redir_pos + 1].was_quoted)
			node->heredoc_no_expand = 1;
	}
	left_count = count_left_tokens(count, redir_pos);
	left_tokens = copy_left_tokens(tokens, count, redir_pos, head);
	if (!left_tokens)
		return (NULL);
	node->left = createast(left_tokens, left_count, head);
	node->right = intializenode(&tokens[redir_pos + 1], 1, head);
	return (node);
}
