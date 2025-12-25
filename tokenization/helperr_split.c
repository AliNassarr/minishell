/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helperr_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 00:00:00 by alnassar         #+#    #+#             */
/*   Updated: 2025/12/24 00:00:00 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

static int	process_variable_size(char *str, int *i, char **pp)
{
	char	varname[1024];
	int		k;

	if (str[*i] == '$' && str[*i + 1] && str[*i + 1] == '?')
	{
		*i += 2;
		return (16);
	}
	else if (str[*i] == '$' && str[*i + 1] && !isdelimeter(str[*i + 1]))
	{
		(*i)++;
		k = 0;
		while (str[*i] && !isdelimeter(str[*i]))
			varname[k++] = str[(*i)++];
		varname[k] = '\0';
		return (getvarsize(varname, pp));
	}
	return (0);
}

int	calculate_expanded_size(char *str, char **pp)
{
	int	i;
	int	size;
	int	var_size;

	i = 0;
	size = 0;
	while (str[i])
	{
		var_size = process_variable_size(str, &i, pp);
		if (var_size > 0)
			size += var_size;
		else
		{
			size++;
			i++;
		}
	}
	return (size + 1);
}

static void	copy_quote_content(char *str, char *result, int *i, int *j)
{
	char	quote;

	quote = str[*i];
	result[(*j)++] = str[(*i)++];
	while (str[*i] && (str[*i] != quote || isbackslash(str, *i)))
		result[(*j)++] = str[(*i)++];
	if (str[*i] == quote)
		result[(*j)++] = str[(*i)++];
}

void	process_quotes_and_spaces(char *str, char *result, int *i, int *j)
{
	if (str[*i] == '"' && !isbackslash(str, *i))
		copy_quote_content(str, result, i, j);
	else if (str[*i] == '\'' && !isbackslash(str, *i))
		copy_quote_content(str, result, i, j);
	else if (str[*i] == '<' || str[*i] == '>' || str[*i] == '|')
		handle_operator(str, result, i, j);
	else if (!spaceis(str[*i]) || (*i > 0 && !spaceis(str[*i - 1])))
		result[(*j)++] = str[(*i)++];
	else
		(*i)++;
}
