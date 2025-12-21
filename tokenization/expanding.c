/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 01:58:52 by invader           #+#    #+#             */
/*   Updated: 2025/12/21 01:53:24 by alnassar         ###   ########.fr       */
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
	char	*variable;
	int		k;
	char	exit_status_str[16];
	extern int	g_last_exit_status;

	k = 0;
	if (varname[0] == '?' && varname[1] == '\0')
	{
		sprintf(exit_status_str, "%d", g_last_exit_status);
		k = 0;
		while (exit_status_str[k])
			expanded[(*j)++] = exit_status_str[k++];
		return ;
	}
	variable = inpp(varname, pp);
	if (variable)
	{
		while (variable[k])
			expanded[(*j)++] = variable[k++];
		return ;
	}
	variable = getenv(varname);
	if (variable)
	{
		while (variable[k])
			expanded[(*j)++] = variable[k++];
	}
}

char	*expand(t_head *head, char *str, char **pp)
{
	int		i;
	int		j;
	char	*expanded;
	char	varname[1024];

	i = 0;
	j = 0;
	expanded = gcmalloc(head, gettotalsize(str, pp));
	if (!expanded)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			getname(str, &i, varname);
			mimic(varname, expanded, &j, pp);
		}
		else if (str[i] == '$' && str[i + 1] && !isdelimeter(str[i + 1]))
		{
			getname(str, &i, varname);
			mimic(varname, expanded, &j, pp);
		}
		else
			expanded[j++] = str[i++];
	}
	expanded[j] = '\0';
	return (expanded);
}

char	*expansion(char *str, t_head *head, int count, char **pp)
{
	int		i;
	t_token	*tokens;

	i = 0;
	tokens = expansionprepartion(str, &count, head);
	if (!tokens)
		return (NULL);
	while (i < count)
	{
		if (tokens[i].expansion == 1)
		{
			tokens[i].str = expand(head, tokens[i].str, pp);
			if (!tokens[i].str)
				return (NULL);
		}
		i++;
	}
	return (joining(head, tokens, count));
}
