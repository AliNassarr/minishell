/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: invader <invader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:03:14 by invader           #+#    #+#             */
/*   Updated: 2025/12/20 00:26:05 by invader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

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
}	t_parse_token;

typedef struct s_treenode
{
	t_parse_token		*tokens;
	int					token_count;
	struct s_treenode	*left;
	struct s_treenode	*right;
}	t_treenode;

#endif