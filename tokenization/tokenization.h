/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 20:58:44 by invader           #+#    #+#             */
/*   Updated: 2025/12/11 15:45:07 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

# include "stdio.h"
# include "stdlib.h"
# include "../builtins/ft_utils.h"

typedef struct s_node
{
	void			*data;
	struct s_node	*next;
}	t_node;

typedef struct s_head
{
	t_node	*head;
}	t_head;

typedef struct s_tree_node
{
	struct s_tree_node	*left;
	struct s_tree_node	*right;
	char				*cmd;
}	t_tree_node;

typedef enum s_type
{
	DQ,
	SQ,
	NQ,
	ER
}	t_type;

typedef struct s_token
{
	char	*str;
	t_type	type;
}	t_token;

t_token	*expansionprepartion(char *str, int *count, t_head *head);
int		counttokens(char *str);
void	*gc_malloc(t_head *head, int size);
void	gc_free_all(t_head *head);
int		isquote(char *str, int i);

#endif
