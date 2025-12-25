/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 00:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/24 21:13:42 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals/signals.h"

static void	handle_quote_error(t_shell *shell, t_head *head)
{
	ft_putendl_fd("minishell: syntax error: unclosed quotes", 2);
	shell->exit_status = 2;
	gcallfree(head);
}

static void	handle_empty_input(t_shell *shell, t_head *head)
{
	shell->exit_status = 0;
	gcallfree(head);
}

static void	handle_syntax_error(t_shell *shell, t_head *head)
{
	ft_putendl_fd("minishell: syntax error near unexpected token", 2);
	shell->exit_status = 2;
	gcallfree(head);
}

static int	process_input(char *str, t_shell *shell, t_head *head)
{
	char	*fixed;

	if (!quotecheck(str))
	{
		handle_quote_error(shell, head);
		return (1);
	}
	fixed = fixspaces(str, head, 0, 0);
	if (!fixed)
	{
		gcallfree(head);
		return (1);
	}
	if (fixed[0] == '\0' || !whitespacecheck(fixed))
	{
		handle_empty_input(shell, head);
		return (1);
	}
	return (0);
}

void	execute_command(t_shell *shell, t_head *head, t_treenode *node);

void	startminishell(char *str, t_shell *shell, char **envp)
{
	char		*fixed;
	t_treenode	*node;
	t_head		*head;

	(void)envp;
	head = intializehead();
	if (!head)
		return ;
	if (process_input(str, shell, head))
		return ;
	fixed = fixspaces(str, head, 0, 0);
	node = asthelper(fixed, head, shell->env);
	if (!node)
	{
		handle_syntax_error(shell, head);
		return ;
	}
	execute_command(shell, head, node);
}
