/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 20:58:44 by invader           #+#    #+#             */
/*   Updated: 2025/12/25 01:41:09 by alnassar         ###   ########.fr       */
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

typedef struct s_join_data
{
	char		*joined;
	int			*j;
	int			*paranthesis;
	t_token		*tokens;
	int			count;
}	t_join_data;

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
void	getname(char *str, int *i, char *varname);
void	mimic(char *varname, char *expanded, int *j, char **pp);
void	mimic_variable(char *varname, char *expanded, int *j, char **pp);
char	*expand(t_head *head, char *str, char **pp);
void	expand_loop(char *str, char *expanded, char **pp);
void	expansion_process(t_token *tokens, int count, char **pp, t_head *head);
int		calculate_expanded_size(char *str, char **pp);
int		getvarsize(char *varname, char **pp);
void	handle_operator(char *str, char *result, int *i, int *j);
void	process_quotes_and_spaces(char *str, char *result, int *i, int *j);
void	mimicp(char *str, char *joined, int *paranthesis, int *j);
void	mimicpq(char *str, char *joined, int *paranthesis, int *j);
void	process_token(t_token *token, char *joined, int *paranthesis, int *j);
void	finalize_joining(t_join_data *data);
void	copy_char_convert_parens(char *str, char *joined, int *i, int *j);

#endif
