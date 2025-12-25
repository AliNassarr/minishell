/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 16:32:12 by invader           #+#    #+#             */
/*   Updated: 2025/12/24 20:25:21 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../utils/ft_utils.h"
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>

/* Forward declarations - actual definitions in minishell.h */
typedef struct s_treenode		t_treenode;
typedef struct s_shell			t_shell;
typedef struct s_head			t_head;
typedef struct s_parse_token	t_parse_token;

/* Main execution function */
int		execute_ast(t_treenode *node, t_shell *shell, t_head *head);

/* Heredoc preparation */
void	prepare_heredocs(t_treenode *node, char **env);
char	*expand_heredoc_line(char *line, char **env);
int		is_var_char(char c);
void	extract_varname(char *line, int *pos, char *varname);
void	reverse_str(char *str, int len);
char	*int_to_str(int n);

/* Helper functions */
char	**extract_command(t_parse_token *tokens, int count, t_head *head);
char	*find_command_path(char *cmd, char **env);
int		execute_simple_command(t_treenode *node, t_shell *shell, t_head *head);
int		handle_redirection(t_treenode *node, t_shell *shell, t_head *head);
int		execute_pipe(t_treenode *node, t_shell *shell, t_head *head);
int		execute_logical(t_treenode *node, t_shell *shell, t_head *head);
int		precreate_output_files(t_treenode *node);

#endif