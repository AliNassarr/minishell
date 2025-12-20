/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: invader <invader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 00:44:37 by invader           #+#    #+#             */
/*   Updated: 2025/12/20 01:09:59 by invader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

t_head	*intializehead(void)
{
	t_head	*head;

	head = malloc(sizeof(t_head));
	if (!head)
		return (NULL);
	head->head = NULL;
	return (head);
}

void	*gcmalloc(t_head *head, int size)
{
	void	*str;
	t_node	*new_node;
	t_node	*current;

	if (!head)
		return (NULL);
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

void	gcallfree(t_head *head)
{
	t_node	*current;
	t_node	*next;

	if (!head)
		return ;
	current = head->head;
	while (current)
	{
		next = current->next;
		free(current->data);
		free(current);
		current = next;
	}
	free(head);
}
