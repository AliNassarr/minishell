/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:03:14 by invader           #+#    #+#             */
/*   Updated: 2025/12/25 01:13:17 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

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

typedef enum e_token_type
{
	PIPE,
	OR,
	AND,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
	CMD,
	ARG,
	FILENAME,
	LIMITER,
	UNKNOWN
}	t_token_type;

typedef struct s_parse_token
{
	char			*str;
	t_token_type	type;
	int				was_quoted;
}	t_parse_token;

typedef struct s_treenode
{
	t_parse_token		*tokens;
	int					token_count;
	int					heredoc_fd;
	int					heredoc_no_expand;
	struct s_treenode	*left;
	struct s_treenode	*right;
}	t_treenode;

void			*gcmalloc(t_head *head, int size);
char			*expansion(char *str, t_head *head, int count, char **pp);
t_parse_token	*parsingprep(char *input, int *count, t_head *head, char **pp);
t_parse_token	*parsetokens(char **words, int count, t_head *head,
					char *joined_str);
int				was_word_quoted(char *str, int word_index);
int				spaceis(char c);
int				ft_strlen(char *str);
int				ft_strcmp(const char *str1, const char *str2);
void			assignoperator(t_parse_token *token, int i);
void			assignfilenames(t_parse_token *tokens, int count);
void			assignrest(t_parse_token *tokens, int count);
int				checkforoperator(t_parse_token *tokens, int count);
int				check_operator_error(t_parse_token *tokens, int i, int count);
void			assign_tokens_types(t_parse_token *tokens, int count,
					char **words, char *joined_str);
void			restore_and_finalize(t_parse_token *tokens, int count);
int				findpipeoperator(t_parse_token *tokens, int start, int end);
int				findrediroperator(t_parse_token *tokens, int start, int end);
t_treenode		*createredirast(t_parse_token *tokens, int count, int oppos,
					t_head *head);
t_treenode		*intializenode(t_parse_token *tokens, int count, t_head *head);
t_treenode		*createast(t_parse_token *tokens, int count, t_head *head);

#endif

/*
	PIPE,           // |
	OR,             // ||
	AND,            // &&
	REDIR_IN,       // <
	REDIR_OUT,      // >
	REDIR_APPEND,   // >>
	HEREDOC,        // <<
	CMD,            // command
	ARG,            // argument
	FILENAME,       // file for redirection
	LIMITER,      // limiter for heredoc
*/