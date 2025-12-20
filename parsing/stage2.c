/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stage2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: invader <invader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:13:22 by invader           #+#    #+#             */
/*   Updated: 2025/12/20 00:18:44 by invader          ###   ########.fr       */
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

	i = 0;
	while (i < count)
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
			if ((tokens[i].type == REDIR_IN || tokens[i].type == REDIR_OUT
					|| tokens[i].type == REDIR_APPEND
					|| tokens[i].type == HEREDOC)
				&& tokens[i + 1].type != UNKNOWN)
				return (1);
		}
		i++;
	}
	return (0);
}

t_parse_token	*parsetokens(char **words, int count, t_head *head)
{
	t_parse_token	*tokens;
	int				i;

	tokens = gcmalloc(head, sizeof(t_parse_token) * count);
	if (!tokens)
		return (NULL);
	i = 0;
	while (i < count)
	{
		tokens[i].str = words[i];
		tokens[i].type = UNKNOWN;
		if (ft_strlen(tokens[i].str) <= 2)
			assignoperator(tokens, i);
		i++;
	}
	if (checkforoperator(tokens, count))
		return (NULL);
	assignfilenames(tokens, count);
	assignrest(tokens, count);
	return (tokens);
}
