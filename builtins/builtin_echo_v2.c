/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo_v2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 15:45:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/11 16:33:57 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_utils.h"

static int	is_flag_n(const char *str)
{
	if (!str)
		return (0);
	if (str[0] == '-' && str[1] == 'n' && str[2] == '\0')
		return (1);
	return (0);
}

int	builtin_echo_str(char **tokens, int count)
{
	int	i;
	int	newline;

	newline = 1;
	i = 1;
	if (count > 1 && is_flag_n(tokens[1]))
	{
		newline = 0;
		i = 2;
	}
	while (i < count)
	{
		if (tokens[i])
			printf("%s", tokens[i]);
		if (i < count - 1)
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
