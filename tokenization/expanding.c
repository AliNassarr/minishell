/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 01:58:52 by invader           #+#    #+#             */
/*   Updated: 2025/12/24 16:47:01 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

int	counttokens(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '"' && (i == 0 || str[i - 1] != '\\'))
		{
			i++;
			while (str[i] && (str[i] != '"' || str[i - 1] == '\\'))
				i++;
			count += 2;
		}
		if (str[i] == '\'' && (i == 0 || str[i - 1] != '\\'))
		{
			i++;
			while (str[i] && (str[i] != '\'' || str[i - 1] == '\\'))
				i++;
			count += 2;
		}
		i++;
	}
	count++;
	return (count);
}

void	getname(char *str, int *i, char *varname)
{
	int	k;

	k = 0;
	(*i)++;
	if (str[*i] == '?')
	{
		varname[k++] = '?';
		(*i)++;
		varname[k] = '\0';
		return ;
	}
	while (str[*i] && !isdelimeter(str[*i]))
		varname[k++] = str[(*i)++];
	varname[k] = '\0';
}

void	mimic(char *varname, char *expanded, int *j, char **pp)
{
	mimic_variable(varname, expanded, j, pp);
}

char	*expand(t_head *head, char *str, char **pp)
{
	char	*expanded;

	expanded = gcmalloc(head, gettotalsize(str, pp));
	if (!expanded)
		return (NULL);
	expand_loop(str, expanded, pp);
	return (expanded);
}

char	*expansion(char *str, t_head *head, int count, char **pp)
{
	t_token	*tokens;

	tokens = expansionprepartion(str, &count, head);
	if (!tokens)
		return (NULL);
	expansion_process(tokens, count, pp, head);
	return (joining(head, tokens, count));
}
