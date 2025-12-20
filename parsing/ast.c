/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 21:40:19 by invader           #+#    #+#             */
/*   Updated: 2025/12/20 21:28:52 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_treenode	*createast(t_parse_token *tokens, int count, t_head *head);

int	operatorcount(t_parse_token *tokens, int count)
{
	int	i;
	int	opcount;

	i = 0;
	opcount = 0;
	while (i < count)
	{
		if (tokens[i].type != CMD && tokens[i].type != ARG)
			opcount++;
		i++;
	}
	return (opcount);
}

t_treenode	*intializenode(t_parse_token *tokens, int count, t_head *head)
{
	t_treenode	*node;

	node = gcmalloc(head, sizeof(t_treenode));
	if (!node)
		return (NULL);
	node->tokens = tokens;
	node->token_count = count;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

int	findpipeoperator(t_parse_token *tokens, int start, int end)
{
	int	i;

	i = start;
	while (i <= end)
	{
		if (tokens[i].type == PIPE || tokens[i].type == OR
			|| tokens[i].type == AND)
			return (i);
		i++;
	}
	return (-1);
}

int	findrediroperator(t_parse_token *tokens, int start, int end)
{
	int	i;

	i = start;
	while (i <= end)
	{
		if (tokens[i].type == REDIR_IN || tokens[i].type == REDIR_OUT
			|| tokens[i].type == REDIR_APPEND || tokens[i].type == HEREDOC)
			return (i);
		i++;
	}
	return (-1);
}

t_treenode	*createredirast(t_parse_token *tokens, int count, int redir_pos,
		t_head *head)
{
	t_treenode	*node;
	t_parse_token	*left_tokens;
	int			left_count;
	int			i;
	int			j;

	node = intializenode(&tokens[redir_pos], 1, head);
	if (!node)
		return (NULL);
	left_count = 0;
	i = 0;
	while (i < count)
	{
		if (i != redir_pos && i != redir_pos + 1)
			left_count++;
		i++;
	}
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
	node->left = createast(left_tokens, left_count, head);
	node->right = intializenode(&tokens[redir_pos + 1], 1, head);
	return (node);
}

t_treenode	*createast(t_parse_token *tokens, int count, t_head *head)
{
	t_treenode	*node;
	int			oppos;
	int			left_count;
	int			right_count;

	if (count == 0)
		return (NULL);
	oppos = findrediroperator(tokens, 0, count - 1);
	if (oppos != -1)
		return (createredirast(tokens, count, oppos, head));
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
