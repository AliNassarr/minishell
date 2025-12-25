/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helperr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 23:18:03 by invader           #+#    #+#             */
/*   Updated: 2025/12/24 16:36:40 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

int	gettotalsize(char *str, char **pp)
{
	return (calculate_expanded_size(str, pp));
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

void	handle_operator(char *str, char *result, int *i, int *j)
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
		process_quotes_and_spaces(str, result, &i, &j);
	}
	return (result[j] = '\0', result);
}
