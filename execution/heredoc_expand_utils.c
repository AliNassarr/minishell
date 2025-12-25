/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 00:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/24 18:02:42 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../utils/ft_utils.h"
#include "../signals/signals.h"
#include <stdlib.h>

int	is_var_char(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || c == '_');
}

void	extract_varname(char *line, int *pos, char *varname)
{
	int	i;

	i = 0;
	(*pos)++;
	if (line[*pos] == '?')
	{
		varname[i++] = '?';
		(*pos)++;
	}
	else
	{
		while (line[*pos] && is_var_char(line[*pos]))
			varname[i++] = line[(*pos)++];
	}
	varname[i] = '\0';
}

void	reverse_str(char *str, int len)
{
	int		i;
	char	tmp;

	i = 0;
	while (i < len / 2)
	{
		tmp = str[i];
		str[i] = str[len - 1 - i];
		str[len - 1 - i] = tmp;
		i++;
	}
}

char	*int_to_str(int n)
{
	char	buf[12];
	int		i;
	int		sign;

	i = 0;
	sign = 0;
	if (n < 0)
	{
		sign = 1;
		n = -n;
	}
	if (n == 0)
		buf[i++] = '0';
	while (n > 0)
	{
		buf[i++] = (n % 10) + '0';
		n /= 10;
	}
	if (sign)
		buf[i++] = '-';
	buf[i] = '\0';
	reverse_str(buf, i);
	return (ft_strdup(buf));
}
