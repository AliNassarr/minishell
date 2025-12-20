/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: invader <invader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 21:40:19 by invader           #+#    #+#             */
/*   Updated: 2025/12/20 17:14:10 by invader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

int	findoperatorpos(t_parse_token *tokens, int start, int end)
{
	int	i;

	i = start;
	while (i <= end)
	{
		if (tokens[i].type != CMD && tokens[i].type != ARG)
			return (i);
		i++;
	}
	return (-1);
}

t_treenode	*createast(t_parse_token *tokens, int count, t_head *head)
{
	t_treenode	*node;
	int			oppos;
	int			left_count;
	int			right_count;

	if (count == 0)
		return (NULL);
	oppos = findoperatorpos(tokens, 0, count - 1);
	if (oppos == -1)
		return (intializenode(tokens, count, head));
	node = intializenode(&tokens[oppos], 1, head);
	if (!node)
		return (NULL);
	left_count = oppos;
	right_count = count - oppos - 1;
	node->left = createast(tokens, left_count, head);
	node->right = createast(&tokens[oppos + 1], right_count, head);
	return (node);
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
