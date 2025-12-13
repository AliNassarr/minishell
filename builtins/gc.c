/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 19:35:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/13 19:54:38 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tokenization/tokenization.h"

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

void	gc_free_all(t_head *head)
{
	t_node	*current;
	t_node	*temp;

	if (!head)
		return ;
	current = head->head;
	while (current != NULL)
	{
		temp = current->next;
		if (current->data)
			free(current->data);
		free(current);
		current = temp;
	}
	head->head = NULL;
}
