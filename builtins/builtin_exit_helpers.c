/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 00:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/24 21:13:42 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		is_numeric(const char *str);
int		has_spaces(const char *str);
char	*get_first_arg(const char *str, t_head *gc);

static int	handle_numeric_check(char *first_arg, t_shell *shell, t_head *gc)
{
	if (!is_numeric(first_arg))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(first_arg, 2);
		ft_putendl_fd(": numeric argument required", 2);
		shell->exit_status = 2;
		shell->should_exit = 1;
		gcallfree(gc);
		return (2);
	}
	gcallfree(gc);
	ft_putendl_fd("exit: too many arguments", 2);
	return (1);
}

int	handle_exit_args(t_shell *shell, char *args)
{
	char	*first_arg;
	t_head	*gc;

	if (has_spaces(args))
	{
		gc = intializehead();
		first_arg = get_first_arg(args, gc);
		return (handle_numeric_check(first_arg, shell, gc));
	}
	return (-1);
}
