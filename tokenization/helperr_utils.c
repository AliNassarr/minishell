/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helperr_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 00:00:00 by alnassar         #+#    #+#             */
/*   Updated: 2025/12/24 00:00:00 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

static void	remove_parentheses(char *joined, int open_pos)
{
	int	i;
	int	j;
	int	depth;

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

void	fix(char *joined, char *str, int count)
{
	int	i;
	int	open_pos;

	if (getlastspace(str) == -1 && count != 1)
		return ;
	i = ft_strlen(joined) - 1;
	while (i >= 0 && joined[i] != '(')
		i--;
	open_pos = i;
	if (open_pos < 0)
		return ;
	remove_parentheses(joined, open_pos);
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
