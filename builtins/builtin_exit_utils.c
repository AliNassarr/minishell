/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 00:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/23 03:35:41 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <limits.h>

int	is_numeric(const char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_atol(const char *str, long *result)
{
	long	num;
	long	sign;
	int		i;

	num = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (sign == 1 && num > (LONG_MAX - (str[i] - '0')) / 10)
			return (0);
		if (sign == -1 && (unsigned long)num
			> ((unsigned long)LONG_MAX + 1 - (str[i] - '0')) / 10)
			return (0);
		num = num * 10 + (str[i] - '0');
		i++;
	}
	*result = num * sign;
	return (1);
}

int	has_spaces(const char *str)
{
	int		i;
	int		in_quote;
	char	quote_char;

	i = 0;
	in_quote = 0;
	quote_char = 0;
	while (str[i])
	{
		if (!in_quote && (str[i] == '"' || str[i] == '\''))
		{
			in_quote = 1;
			quote_char = str[i];
		}
		else if (in_quote && str[i] == quote_char)
			in_quote = 0;
		else if (!in_quote && str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

char	*get_first_arg(const char *str, t_head *gc)
{
	int		i;
	char	*result;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	result = gcmalloc(gc, i + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != ' ')
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
