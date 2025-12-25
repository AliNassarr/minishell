/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stage2_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 00:00:00 by alnassar         #+#    #+#             */
/*   Updated: 2025/12/24 00:00:00 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	restore_parentheses(char *str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\x01')
			str[i] = '(';
		else if (str[i] == '\x02')
			str[i] = ')';
		i++;
	}
}

static int	check_redir_operator(t_parse_token *tokens, int i)
{
	if ((tokens[i].type == REDIR_IN || tokens[i].type == REDIR_OUT
			|| tokens[i].type == REDIR_APPEND
			|| tokens[i].type == HEREDOC)
		&& tokens[i + 1].type != UNKNOWN)
		return (1);
	return (0);
}

int	check_operator_error(t_parse_token *tokens, int i, int count)
{
	if (tokens[i].type == PIPE || tokens[i].type == AND
		|| tokens[i].type == OR || tokens[i].type == REDIR_IN
		|| tokens[i].type == REDIR_OUT || tokens[i].type == REDIR_APPEND
		|| tokens[i].type == HEREDOC)
	{
		if (i + 1 >= count)
			return (1);
		if (tokens[i + 1].type == PIPE || tokens[i + 1].type == AND
			|| tokens[i + 1].type == OR)
			return (1);
		if (check_redir_operator(tokens, i))
			return (1);
	}
	return (0);
}

void	assign_tokens_types(t_parse_token *tokens, int count, char **words,
	char *joined_str)
{
	int	i;
	int	was_quoted;

	i = 0;
	while (i < count)
	{
		tokens[i].str = words[i];
		tokens[i].type = UNKNOWN;
		was_quoted = was_word_quoted(joined_str, i);
		tokens[i].was_quoted = was_quoted;
		if (ft_strlen(tokens[i].str) <= 2)
			assignoperator(tokens, i);
		i++;
	}
}

void	restore_and_finalize(t_parse_token *tokens, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		restore_parentheses(tokens[i].str);
		i++;
	}
}
