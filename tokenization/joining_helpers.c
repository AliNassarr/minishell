/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joining_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 00:00:00 by alnassar         #+#    #+#             */
/*   Updated: 2025/12/24 00:00:00 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

void	copy_char_convert_parens(char *str, char *joined, int *i, int *j)
{
	if (str[*i] == '(')
		joined[(*j)++] = '\x01';
	else if (str[*i] == ')')
		joined[(*j)++] = '\x02';
	else
		joined[(*j)++] = str[*i];
	(*i)++;
}

void	process_token(t_token *token, char *joined, int *paranthesis, int *j)
{
	if (token->type != NQ && token->str)
		mimicp(token->str, joined, paranthesis, j);
	else
		mimicpq(token->str, joined, paranthesis, j);
}

void	finalize_joining(t_join_data *data)
{
	if (*(data->paranthesis) == 1)
		data->joined[(*(data->j))++] = ')';
	data->joined[*(data->j)] = '\0';
	if (data->count > 0 && data->tokens[data->count - 1].type == NQ
		&& data->tokens[data->count - 1].str != NULL)
		fix(data->joined, data->tokens[data->count - 1].str, data->count);
}
