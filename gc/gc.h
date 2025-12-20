/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: invader <invader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 00:44:57 by invader           #+#    #+#             */
/*   Updated: 2025/12/20 00:45:31 by invader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H

# include <stdio.h>
# include <stdlib.h>

typedef struct s_node
{
	void			*data;
	struct s_node	*next;
}	t_node;

typedef struct s_head
{
	t_node	*head;
}	t_head;

#endif