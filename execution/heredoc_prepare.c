/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_prepare.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 00:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/24 03:16:33 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"
#include "../utils/ft_utils.h"
#include <readline/readline.h>

static void	read_heredoc_lines(int pipe_fd, char *limiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			write(2, "minishell: here-document delimited by end-of-file\n", 51);
			break ;
		}
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipe_fd, line, ft_strlen(line));
		write(pipe_fd, "\n", 1);
		free(line);
	}
}

static int	prepare_single_heredoc(t_treenode *node)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("minishell: pipe");
		return (-1);
	}
	read_heredoc_lines(pipe_fd[1], node->right->tokens[0].str);
	close(pipe_fd[1]);
	node->heredoc_fd = pipe_fd[0];
	return (0);
}

void	prepare_heredocs(t_treenode *node)
{
	if (!node)
		return ;
	if (node->token_count == 1 && node->tokens[0].type == HEREDOC)
	{
		if (prepare_single_heredoc(node) == -1)
			node->heredoc_fd = -1;
	}
	prepare_heredocs(node->left);
	prepare_heredocs(node->right);
}
