/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 16:32:12 by invader           #+#    #+#             */
/*   Updated: 2025/12/20 21:26:26 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>

/* Forward declarations - actual definitions in minishell.h */
typedef struct s_treenode	t_treenode;
typedef struct s_shell		t_shell;
typedef struct s_head		t_head;
typedef struct s_parse_token	t_parse_token;

/* Main execution function */
int		execute_ast(t_treenode *node, t_shell *shell, t_head *head);

/* Helper functions */
char	**extract_command(t_parse_token *tokens, int count, t_head *head);
char	*find_command_path(char *cmd, char **env);
int		execute_simple_command(t_treenode *node, t_shell *shell, t_head *head);
int		handle_redirection(t_treenode *node, t_shell *shell, t_head *head);
int		execute_pipe(t_treenode *node, t_shell *shell, t_head *head);
int		execute_logical(t_treenode *node, t_shell *shell, t_head *head);

#endif