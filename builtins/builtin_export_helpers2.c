/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_helpers2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 00:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/24 21:13:42 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		has_special_chars_in_value(const char *str);
int		is_valid_identifier(const char *str);
int		find_equals_sign(const char *str);
char	*extract_key(const char *str, int equals_pos, t_head *gc);

static int	check_option(char *str)
{
	if (str[0] == '-')
	{
		ft_putstr_fd("export: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": invalid option", 2);
		return (2);
	}
	return (0);
}

static int	check_special_chars(char *str)
{
	if (has_special_chars_in_value(str))
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return (2);
	}
	return (0);
}

static int	check_identifier(char *str)
{
	if (!is_valid_identifier(str))
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return (1);
	}
	return (0);
}
