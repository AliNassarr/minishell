/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stage1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: invader <invader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 20:08:44 by invader           #+#    #+#             */
/*   Updated: 2025/12/20 02:57:53 by invader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

t_token	handledoublequote(char *str, int *j, int *i, t_head *head)
{
	int		k;
	int		temp;
	t_token	token;

	(*i)++;
	temp = (*i);
	while (str[temp] && (str[temp] != '"' || isbackslash(str, temp)))
		temp++;
	token.str = gcmalloc(head, (temp - (*i)) + 1);
	if (!token.str)
		return (token.type = ER, token);
	token.type = DQ;
	token.expansion = 0;
	k = 0;
	while (str[*i] && (str[*i] != '"' || isbackslash(str, *i)))
	{
		if (str[*i] == '$')
			token.expansion = 1;
		token.str[k] = str[*i];
		k++;
		(*i)++;
	}
	token.str[k] = '\0';
	(*i)++;
	return (*j = *i, token);
}

t_token	handlesinglequote(char *str, int *j, int *i, t_head *head)
{
	int		k;
	int		temp;
	t_token	token;

	(*i)++;
	temp = (*i);
	while (str[temp] && (str[temp] != '\'' || isbackslash(str, temp)))
		temp++;
	token.str = gcmalloc(head, (temp - (*i)) + 1);
	if (!token.str)
		return (token.type = ER, token);
	token.expansion = 0;
	token.type = SQ;
	k = 0;
	while (str[*i] && (str[*i] != '\'' || isbackslash(str, *i)))
	{
		token.str[k] = str[*i];
		k++;
		(*i)++;
	}
	token.str[k] = '\0';
	(*i)++;
	*j = *i;
	return (token);
}

t_token	handlenoquote(char *str, int start, int end, t_head *head)
{
	int		k;
	t_token	token;

	token.expansion = 0;
	token.type = NQ;
	if (end - start == 0)
	{
		token.str = NULL;
		return (token);
	}
	token.str = gcmalloc(head, sizeof(char) * (end - start + 1));
	if (!token.str)
		return (token.type = ER, token);
	k = 0;
	while (start < end)
	{
		if (str[start] == '$')
			token.expansion = 1;
		token.str[k] = str[start];
		start++;
		k++;
	}
	token.str[k] = '\0';
	return (token);
}

t_token	*intializetoken(char *str, t_head *head)
{
	int		size;
	t_token	*tokens;

	size = 0;
	size = counttokens(str);
	if (size == 0)
		return (NULL);
	tokens = gcmalloc(head, sizeof(t_token) * size);
	if (!tokens)
		return (NULL);
	return (tokens);
}

t_token	*expansionprepartion(char *str, int *count, t_head *head)
{
	int		i;
	int		j;
	t_token	*tokens;

	tokens = intializetoken(str, head);
	if (!tokens)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '"' && (i == 0 || !isbackslash(str, i)))
		{
			tokens[(*count)++] = handlenoquote(str, j, i, head);
			tokens[(*count)++] = handledoublequote(str, &j, &i, head);
		}
		if (str[i] && str[i] == '\'' && (i == 0 || !isbackslash(str, i)))
		{
			tokens[(*count)++] = handlenoquote(str, j, i, head);
			tokens[(*count)++] = handlesinglequote(str, &j, &i, head);
		}
		if (str[i] && !isquote(str, i))
			i++;
	}
	return (tokens[(*count)++] = handlenoquote(str, j, i, head), tokens);
}
