/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparation_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 00:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/25 01:13:17 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	skip_quoted_word(char *str, int *i)
{
	(*i)++;
	while (str[*i] && str[*i] != ')')
		(*i)++;
	if (str[*i])
		(*i)++;
}

static void	skip_unquoted_word(char *str, int *i)
{
	while (str[*i] && !spaceis(str[*i]))
		(*i)++;
}

int	was_word_quoted(char *str, int word_index)
{
	int	i;
	int	current_word;

	if (!str)
		return (0);
	i = 0;
	current_word = 0;
	while (str[i] && current_word < word_index)
	{
		if (str[i] == '(')
			skip_quoted_word(str, &i);
		else
			skip_unquoted_word(str, &i);
		if (str[i] && spaceis(str[i]))
			i++;
		current_word++;
	}
	return (str[i] == '(');
}
