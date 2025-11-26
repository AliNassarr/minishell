/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: invader <invader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:29:32 by invader           #+#    #+#             */
/*   Updated: 2025/11/26 17:49:44 by invader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

void	*gc_malloc(t_head *head, int size)
{
	void	*str;
	t_node	*new_node;
	t_node	*current;

	str = malloc(size);
	if (!str)
		return (NULL);
	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (free(str), NULL);
	new_node->data = str;
	new_node->next = NULL;
	if (head->head == NULL)
		head->head = new_node;
	else
	{
		current = head->head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
	return (str);
}

int	isquote(char *str, int i)
{
	if ((i == 0 || str[i - 1] != '\\') && (str[i] == '"' || str[i] == '\'' ))
		return (1);
	return (0);
}

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

int	main(int argc, char *argv[])
{
	t_head	head;
	t_token	*tokens;
	int		i;
	int		count;

	if (argc < 2)
		return (1);
	head.head = NULL;
	count = 0;
	tokens = expansionprepartion(argv[1], &count, &head);
	if (!tokens)
		return (1);
	i = 0;
	while (i < count)
	{
		if (tokens[i].str)
			printf("Token %d: [%s] Type: %d\n", i,
				tokens[i].str, tokens[i].type);
		else
			printf("Token %d: [NULL] Type: %d\n", i, tokens[i].type);
		i++;
	}
	return (0);
}
