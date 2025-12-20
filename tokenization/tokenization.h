/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: invader <invader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 20:58:44 by invader           #+#    #+#             */
/*   Updated: 2025/12/20 03:25:11 by invader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

# include "stdio.h"
# include "stdlib.h"

typedef struct s_node
{
	void			*data;
	struct s_node	*next;
}	t_node;

typedef struct s_head
{
	t_node	*head;
}	t_head;

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
	int		expansion;
}	t_token;

void	*gcmalloc(t_head *head, int size);
char	*joining(t_head *head, t_token *tokens, int count);
t_token	*expansionprepartion(char *str, int *count, t_head *head);
int		counttokens(char *str);
int		isquote(char *str, int i);
int		spaceis(char c);
char	*inpp(char *varname, char **pp);
int		isbackslash(char *str, int i);
int		ft_strlen(char *str);
int		isdelimeter(char c);
int		gettotalsize(char *str, char **pp);
int		getlastspace(char *str);
void	fix(char *joined, char *str, int count);

#endif
