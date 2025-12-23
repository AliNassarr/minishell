/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_helpers2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 00:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/23 03:35:41 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals/signals.h"

void	execute_command(t_shell *shell, t_head *head, t_treenode *node)
{
	int	exit_status;

	setupexecution();
	exit_status = execute_ast(node, shell, head);
	setupinteractive();
	shell->exit_status = exit_status;
	g_last_exit_status = exit_status;
	gcallfree(head);
}
