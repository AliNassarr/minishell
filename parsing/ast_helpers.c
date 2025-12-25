/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 00:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/24 16:36:40 by alnassar         ###   ########.fr       */
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

int	findpipeoperator(t_parse_token *tokens, int start, int end)
{
	int	i;

	i = end;
	while (i >= start)
	{
		if (tokens[i].type == PIPE || tokens[i].type == OR
			|| tokens[i].type == AND)
			return (i);
		i--;
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
