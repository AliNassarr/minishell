/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_prepare.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 00:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/25 01:13:17 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"
#include "../utils/ft_utils.h"
#include "../signals/signals.h"
#include <readline/readline.h>

static void	write_heredoc_line(int pipe_fd, char *line, char **env,
	int no_expand)
{
	char	*expanded;

	if (no_expand)
		expanded = line;
	else
		expanded = expand_heredoc_line(line, env);
	write(pipe_fd, expanded, ft_strlen(expanded));
	write(pipe_fd, "\n", 1);
	if (!no_expand)
		free(expanded);
}

static void	read_heredoc_lines(int pipe_fd, char *limiter, char **env,
	int no_expand)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			if (g_signal & SIGINT)
			{
				g_signal = (130 << 16) | (g_signal & 0x1FF);
				break ;
			}
			write(2, "minishell: here-document delimited by end-of-file\n", 51);
			break ;
		}
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		write_heredoc_line(pipe_fd, line, env, no_expand);
		free(line);
	}
}

static int	prepare_single_heredoc(t_treenode *node, char **env)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("minishell: pipe");
		return (-1);
	}
	read_heredoc_lines(pipe_fd[1], node->right->tokens[0].str, env,
		node->heredoc_no_expand);
	close(pipe_fd[1]);
	if (g_signal & SIGINT)
	{
		close(pipe_fd[0]);
		return (-1);
	}
	node->heredoc_fd = pipe_fd[0];
	return (0);
}

void	prepare_heredocs(t_treenode *node, char **env)
{
	if (!node)
		return ;
	if (node->token_count == 1 && node->tokens[0].type == HEREDOC)
	{
		if (prepare_single_heredoc(node, env) == -1)
			node->heredoc_fd = -1;
	}
	prepare_heredocs(node->left, env);
	prepare_heredocs(node->right, env);
}
