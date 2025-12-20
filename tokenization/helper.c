/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: invader <invader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:29:32 by invader           #+#    #+#             */
/*   Updated: 2025/12/20 01:04:23 by invader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

int	isdelimeter(char c)
{
	if (c == '\0' || c == '\'' || c == '"' || c == '$' || c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	spaceis(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	isquote(char *str, int i)
{
	if ((i == 0 || str[i - 1] != '\\') && (str[i] == '"' || str[i] == '\'' ))
		return (1);
	return (0);
}

int	isbackslash(char *str, int i)
{
	int	count;

	if (i == 0)
		return (0);
	count = 0;
	i--;
	while (i >= 0 && str[i] == '\\')
	{
		count++;
		i--;
	}
	if (count % 2 == 1)
		return (1);
	return (0);
}

char	*inpp(char *varname, char **pp)
{
	int	i;
	int	j;

	if (!pp)
		return (NULL);
	i = 0;
	while (pp[i])
	{
		j = 0;
		while (varname[j] && pp[i][j] && varname[j] == pp[i][j])
			j++;
		if (varname[j] == '\0' && pp[i][j] == '=')
			return (&pp[i][j + 1]);
		i++;
	}
	return (NULL);
}
