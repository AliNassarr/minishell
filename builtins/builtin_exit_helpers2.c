/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_helpers2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 00:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/23 03:35:41 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		is_numeric(const char *str);
int		ft_atol(const char *str, long *result);

static int	handle_non_numeric(t_shell *shell, char *args)
{
	fprintf(stderr, "exit: %s: numeric argument required\n", args);
	shell->exit_status = 2;
	shell->should_exit = 1;
	return (2);
}

int	process_numeric_arg(t_shell *shell, char *args)
{
	long	exit_code;
	int		final_code;

	if (!is_numeric(args))
		return (handle_non_numeric(shell, args));
	if (!ft_atol(args, &exit_code))
		return (handle_non_numeric(shell, args));
	final_code = (int)((exit_code % 256 + 256) % 256);
	shell->should_exit = 1;
	return (final_code);
}
