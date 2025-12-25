/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 23:00:00 by invader           #+#    #+#             */
/*   Updated: 2025/12/25 01:13:17 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	wordcount(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		count++;
		if (str[i] == '(')
		{
			i++;
			while (str[i] != ')')
				i++;
			i++;
		}
		else
		{
			while (str[i] && !spaceis(str[i]))
				i++;
		}
		if (spaceis(str[i]))
			i++;
	}
	return (count);
}

int	wordsize(char *str)
{
	int	size;
	int	i;

	size = 0;
	i = 0;
	if (str[i] == '(')
	{
		i++;
		while (str[i] && str[i] != ')')
		{
			size++;
			i++;
		}
		return (size);
	}
	while (str[i] && !spaceis(str[i]))
	{
		size++;
		i++;
	}
	return (size);
}

char	*getword(char *str, int *i, t_head *head)
{
	char	*word;
	int		size;
	int		j;

	size = wordsize(str + *i);
	word = gcmalloc(head, size + 1);
	if (!word)
		return (NULL);
	j = 0;
	if (str[*i] == '(')
	{
		(*i)++;
		while (str[*i] && str[*i] != ')')
			word[j++] = str[(*i)++];
		(*i)++;
	}
	else
	{
		while (str[*i] && !spaceis(str[*i]))
			word[j++] = str[(*i)++];
	}
	word[j] = '\0';
	if (spaceis(str[*i]))
		(*i)++;
	return (word);
}

t_parse_token	*parsingprep(char *input, int *count, t_head *head, char **pp)
{
	char	**parsed;
	char	*str;
	int		i;
	int		j;

	str = expansion(input, head, 0, pp);
	if (!str)
		return (NULL);
	(*count) = wordcount(str);
	parsed = gcmalloc(head, sizeof(char *) * ((*count) + 1));
	if (!parsed)
		return (NULL);
	i = 0;
	j = 0;
	while (j < (*count))
	{
		parsed[j] = getword(str, &i, head);
		if (!parsed[j])
			return (NULL);
		j++;
	}
	parsed[j] = NULL;
	return (parsetokens(parsed, j, head, str));
}
