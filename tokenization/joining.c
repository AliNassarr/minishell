/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joining.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: invader <invader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:26:33 by invader           #+#    #+#             */
/*   Updated: 2025/12/20 03:24:18 by invader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

int	getlastspace(char *str)
{
	int	i;
	int	last;

	if (!str)
		return (-1);
	i = 0;
	last = -1;
	while (str[i])
	{
		if (spaceis(str[i]))
			last = i;
		i++;
	}
	return (last);
}

void	mimicp(char *str, char *joined, int *paranthesis, int *j)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	if (*paranthesis == 0)
	{
		joined[(*j)++] = '(';
		*paranthesis = 1;
	}
	while (str[i])
		joined[(*j)++] = str[i++];
}

void	mimicpq(char *str, char *joined, int *paranthesis, int *j)
{
	int	i;

	if (!str || str[0] == '\0')
		return ;
	i = 0;
	if (getlastspace(str) == -1)
		return (mimicp(str, joined, paranthesis, j));
	else if (*paranthesis == 1)
	{
		while (str[i] && !spaceis(str[i]))
			joined[(*j)++] = str[i++];
		joined[(*j)++] = ')';
		*paranthesis = 0;
	}
	while (str[i])
	{
		if (i == getlastspace(str))
		{
			joined[(*j)++] = str[i++];
			joined[(*j)++] = '(';
			*paranthesis = 1;
		}
		else
			joined[(*j)++] = str[i++];
	}
}

int	joinsize(t_token *tokens, int count)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (i < count)
	{
		size += ft_strlen(tokens[i].str);
		if (tokens[i].type != NQ)
			size += 2;
		i++;
	}
	size++;
	return (size);
}

char	*joining(t_head *head, t_token *tokens, int count)
{
	int		i;
	int		j;
	int		paranthesis;
	char	*joined;

	i = 0;
	j = 0;
	paranthesis = 0;
	joined = gcmalloc(head, joinsize(tokens, count));
	if (!joined)
		return (NULL);
	while (i < count)
	{
		if (tokens[i].type != NQ && tokens[i].str)
			mimicp(tokens[i].str, joined, &paranthesis, &j);
		else
			mimicpq(tokens[i].str, joined, &paranthesis, &j);
		i++;
	}
	if (paranthesis == 1)
		joined[j++] = ')';
	joined[j] = '\0';
	if (tokens[count - 1].type == NQ && tokens[count -1].str != NULL)
		fix(joined, tokens[count - 1].str, count);
	return (joined);
}

///NQ if there isnt space and we have paranthesis we should keep them
///NQ if there isnt space and we have no paranthesis we should check them
///NQ if there is space and we have paranthesis we should close them
///NQ if ther is space and we have no paranthesis we should keepthem
/*
while (i < count)
	{
		if (tokens[i].str == NULL)
		{
			i++;
			continue ;
		}
		printf("%s:\n", tokens[i].str);
		i++;
	}
		
*/