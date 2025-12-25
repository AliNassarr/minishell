/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stage2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:13:22 by invader           #+#    #+#             */
/*   Updated: 2025/12/25 01:13:17 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	assignoperator(t_parse_token *token, int i)
{
	int	len;

	len = ft_strlen(token[i].str);
	if (len == 2)
	{
		if (ft_strcmp(token[i].str, "||") == 0)
			token[i].type = OR;
		if (ft_strcmp(token[i].str, "&&") == 0)
			token[i].type = AND;
		if (ft_strcmp(token[i].str, "<<") == 0)
			token[i].type = HEREDOC;
		if (ft_strcmp(token[i].str, ">>") == 0)
			token[i].type = REDIR_APPEND;
	}
	else
	{
		if (token[i].str[0] == '|')
			token[i].type = PIPE;
		if (token[i].str[0] == '<')
			token[i].type = REDIR_IN;
		if (token[i].str[0] == '>')
			token[i].type = REDIR_OUT;
	}
}

void	assignfilenames(t_parse_token *tokens, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (tokens[i].type == REDIR_IN || tokens[i].type == REDIR_OUT
			|| tokens[i].type == REDIR_APPEND || tokens[i].type == HEREDOC)
		{
			if (i + 1 < count)
			{
				if (tokens[i].type == HEREDOC)
					tokens[i + 1].type = LIMITER;
				else
					tokens[i + 1].type = FILENAME;
			}
		}
		i++;
	}
}

void	assignrest(t_parse_token *tokens, int count)
{
	int		i;
	int		cmdexist;

	i = 0;
	cmdexist = 0;
	while (i < count)
	{
		if (tokens[i].type == PIPE || tokens[i].type == AND
			|| tokens[i].type == OR)
			cmdexist = 0;
		else if (tokens[i].type == UNKNOWN)
		{
			if (!cmdexist)
			{
				tokens[i].type = CMD;
				cmdexist = 1;
			}
			else
				tokens[i].type = ARG;
		}
		i++;
	}
}

int	checkforoperator(t_parse_token *tokens, int count)
{
	int	i;

	if (count == 0)
		return (0);
	if (tokens[0].type == PIPE || tokens[0].type == AND
		|| tokens[0].type == OR)
		return (1);
	i = 0;
	while (i < count)
	{
		if (check_operator_error(tokens, i, count))
			return (1);
		i++;
	}
	return (0);
}

t_parse_token	*parsetokens(char **words, int count, t_head *head,
	char *joined_str)
{
	t_parse_token	*tokens;

	tokens = gcmalloc(head, sizeof(t_parse_token) * count);
	if (!tokens)
		return (NULL);
	assign_tokens_types(tokens, count, words, joined_str);
	if (checkforoperator(tokens, count))
		return (NULL);
	assignfilenames(tokens, count);
	assignrest(tokens, count);
	restore_and_finalize(tokens, count);
	return (tokens);
}
