/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_helpers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 00:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/23 03:35:41 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		is_valid_identifier(const char *str);
int		find_equals_sign(const char *str);
char	*extract_key(const char *str, int equals_pos, t_head *gc);
int		has_special_chars_in_value(const char *str);

static int	check_option_error(char *str)
{
	if (str[0] == '-')
	{
		fprintf(stderr, "export: %s: invalid option\n", str);
		return (2);
	}
	if (has_special_chars_in_value(str))
	{
		fprintf(stderr, "export: `%s': not a valid identifier\n", str);
		return (2);
	}
	if (!is_valid_identifier(str))
	{
		fprintf(stderr, "export: `%s': not a valid identifier\n", str);
		return (1);
	}
	return (0);
}

int	process_export_arg(t_shell *shell, char *str)
{
	int		equals_pos;
	char	*key;
	char	*value;
	int		ret;

	ret = check_option_error(str);
	if (ret != 0)
		return (ret);
	equals_pos = find_equals_sign(str);
	if (equals_pos == -1)
		return (0);
	key = extract_key(str, equals_pos, shell->env_gc);
	if (!key)
		return (1);
	value = &str[equals_pos + 1];
	shell->env = set_env_value(shell->env, key, value, shell->env_gc);
	return (0);
}
