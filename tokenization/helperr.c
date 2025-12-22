/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helperr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 23:18:03 by invader           #+#    #+#             */
/*   Updated: 2025/12/22 01:48:07 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

void	fix(char *joined, char *str, int count)
{
	int	i;
	int	j;
	int	open_pos;
	int	depth;

	if (getlastspace(str) == -1 && count != 1)
		return ;
	i = ft_strlen(joined) - 1;
	while (i >= 0 && joined[i] != '(')
		i--;
	open_pos = i;
	if (open_pos < 0)
		return ;
	i = open_pos + 1;
	j = open_pos;
	depth = 1;
	while (joined[i] && depth > 0)
	{
		if (joined[i] == '(')
			depth++;
		else if (joined[i] == ')')
			depth--;
		if (depth > 0)
			joined[j++] = joined[i];
		i++;
	}
	while (joined[i])
		joined[j++] = joined[i++];
	joined[j] = '\0';
}

int	getvarsize(char *varname, char **pp)
{
	char	*value;

	if (varname[0] == '?' && varname[1] == '\0')
		return (16);
	value = inpp(varname, pp);
	if (value)
		return (ft_strlen(value));
	value = getenv(varname);
	return (ft_strlen(value));
}

int	gettotalsize(char *str, char **pp)
{
	int		i;
	int		size;
	char	varname[1024];
	int		k;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] == '?')
		{
			size += 16;
			i += 2;
		}
		else if (str[i] == '$' && str[i + 1] && !isdelimeter(str[i + 1]))
		{
			i++;
			k = 0;
			while (str[i] && !isdelimeter(str[i]))
				varname[k++] = str[i++];
			varname[k] = '\0';
			size += getvarsize(varname, pp);
		}
		else
		{
			size++;
			i++;
		}
	}
	return (size + 1);
}

int	quotecheck(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' && !isbackslash(str, i))
		{
			i++;
			while (str[i] && (str[i] != '"' || isbackslash(str, i)))
				i++;
			if (str[i] != '"')
				return (0);
		}
		if (str[i] == '\'' && !isbackslash(str, i))
		{
			i++;
			while (str[i] && (str[i] != '\'' || isbackslash(str, i)))
				i++;
			if (str[i] != '\'')
				return (0);
		}
		i++;
	}
	return (1);
}

static int	count_operator_spaces(char *str)
{
	int	i;
	int	extra;
	int	in_quote;

	i = 0;
	extra = 0;
	in_quote = 0;
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\'') && !isbackslash(str, i))
			in_quote = !in_quote;
		if (!in_quote && (str[i] == '<' || str[i] == '>' || str[i] == '|'))
		{
			if (i > 0 && str[i - 1] != ' ' && str[i - 1] != str[i])
				extra++;
			if (str[i + 1] && str[i + 1] != ' ' && str[i + 1] != str[i])
				extra++;
		}
		i++;
	}
	return (extra);
}

static void	handle_operator(char *str, char *result, int *i, int *j)
{
	if (*i > 0 && str[*i - 1] != ' ' && result[*j - 1] != ' ')
		result[(*j)++] = ' ';
	result[(*j)++] = str[*i];
	if (str[*i + 1] == str[*i])
	{
		(*i)++;
		result[(*j)++] = str[*i];
	}
	if (str[*i + 1] && str[*i + 1] != ' ')
		result[(*j)++] = ' ';
	(*i)++;
}

char	*fixspaces(char *str, t_head *head, int i, int j)
{
	char	*result;

	result = gcmalloc(head, ft_strlen(str) + count_operator_spaces(str) + 1);
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '"' && !isbackslash(str, i))
		{
			result[j++] = str[i++];
			while (str[i] && (str[i] != '"' || isbackslash(str, i)))
				result[j++] = str[i++];
			if (str[i] == '"')
				result[j++] = str[i++];
		}
		else if (str[i] == '\'' && !isbackslash(str, i))
		{
			result[j++] = str[i++];
			while (str[i] && (str[i] != '\'' || isbackslash(str, i)))
				result[j++] = str[i++];
			if (str[i] == '\'')
				result[j++] = str[i++];
		}
		else if (str[i] == '<' || str[i] == '>' || str[i] == '|')
			handle_operator(str, result, &i, &j);
		else if (!spaceis(str[i]) || (i > 0 && !spaceis(str[i - 1])))
			result[j++] = str[i++];
		else
			i++;
	}
	return (result[j] = '\0', result);
}
