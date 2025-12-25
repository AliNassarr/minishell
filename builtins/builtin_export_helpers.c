/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_helpers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 00:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/25 02:06:02 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		is_valid_identifier(const char *str);
int		find_equals_sign(const char *str);
char	*extract_key(const char *str, int equals_pos, t_head *gc);
int		has_special_chars_in_value(const char *str);

static void	print_export_error(char *str, char *msg, int use_backticks)
{
	ft_putstr_fd("export: ", 2);
	if (use_backticks)
		ft_putstr_fd("`", 2);
	ft_putstr_fd(str, 2);
	if (use_backticks)
		ft_putstr_fd("'", 2);
	ft_putendl_fd(msg, 2);
}

static int	check_option_error(char *str)
{
	if (str[0] == '-')
	{
		print_export_error(str, ": invalid option", 0);
		return (2);
	}
	if (str[0] == '(' || str[0] == ')')
	{
		print_export_error(str, ": not a valid identifier", 1);
		return (1);
	}
	if (has_special_chars_in_value(str))
	{
		print_export_error(str, ": not a valid identifier", 1);
		return (2);
	}
	if (!is_valid_identifier(str))
	{
		print_export_error(str, ": not a valid identifier", 1);
		return (1);
	}
	return (0);
}

static int	set_export_value(t_shell *shell, char *str, int equals_pos)
{
	char	*key;
	char	*value;

	key = extract_key(str, equals_pos, shell->env_gc);
	if (!key)
		return (1);
	value = &str[equals_pos + 1];
	shell->env = set_env_value(shell->env, key, value, shell->env_gc);
	return (0);
}

int	process_export_arg(t_shell *shell, char *str)
{
	int		equals_pos;
	int		ret;

	ret = check_option_error(str);
	if (ret != 0)
		return (ret);
	equals_pos = find_equals_sign(str);
	if (equals_pos == -1)
	{
		shell->env = set_env_value(shell->env, str, NULL, shell->env_gc);
		return (0);
	}
	return (set_export_value(shell, str, equals_pos));
}
