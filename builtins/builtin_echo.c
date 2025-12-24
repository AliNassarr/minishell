/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 15:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/24 04:18:54 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../utils/ft_utils.h"

static int	is_n_flag(char *str, int *i)
{
	int	j;

	if (str[*i] != '-' || str[*i + 1] != 'n')
		return (0);
	j = *i + 1;
	while (str[j] == 'n')
		j++;
	if (str[j] != ' ' && str[j] != '\0')
		return (0);
	*i = j;
	if (str[j] == ' ')
		(*i)++;
	return (1);
}

void	builtin_echo(char *str)
{
	int	no_newline;
	int	i;

	no_newline = 0;
	if (!str)
		return ((void)printf("\n"));
	i = 0;
	while (is_n_flag(str, &i))
		no_newline = 1;
	if (str[i] != '\0')
		printf("%s", &str[i]);
	if (!no_newline)
		printf("\n");
}
