/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helperr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: invader <invader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 23:18:03 by invader           #+#    #+#             */
/*   Updated: 2025/12/20 03:24:35 by invader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

void	fix(char *joined, char *str, int count)
{
	int	i;
	int	j;
	int	open_pos;

	if (getlastspace(str) == -1 && count != 1)
		return ;
	i = ft_strlen(joined) - 1;
	while (i >= 0 && joined[i] != '(')
		i--;
	open_pos = i;
	j = open_pos;
	i = open_pos + 1;
	while (joined[i])
	{
		if (joined[i] != ')')
			joined[j++] = joined[i];
		i++;
	}
	joined[j] = '\0';
}

int	getvarsize(char *varname, char **pp)
{
	char	*value;

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
		if (str[i] == '$' && str[i + 1] && !isdelimeter(str[i + 1]))
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

char	*fixspaces(char *str, t_head *head, int i, int j)
{
	char	*result;

	result = gcmalloc(head, ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '"' && !isbackslash(str, i))
		{
			result[j++] = str[i++];
			while (str[i] != '"' || isbackslash(str, i))
				result[j++] = str[i++];
		}
		if (str[i] == '\'' && !isbackslash(str, i))
		{
			result[j++] = str[i++];
			while (str[i] != '\'' || isbackslash(str, i))
				result[j++] = str[i++];
		}
		if (!spaceis(str[i]) || (i > 0 && !spaceis(str[i - 1])))
			result[j++] = str[i++];
		else
			i++;
	}
	return (result[j] = '\0', result);
}
