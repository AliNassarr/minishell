/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 15:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/21 03:00:30 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../utils/ft_utils.h"

void	builtin_echo(char *str)
{
	int	no_newline;
	int	i;

	no_newline = 0;
	if (!str)
		return ((void)printf("\n"));
	i = 0;
	while (str[i] == '-' && str[i + 1] == 'n' && str[i + 2] == ' ')
	{
		no_newline = 1;
		i += 3;
	}
	if (str[i] == '-' && str[i + 1] == 'n' && str[i + 2] == '\0')
	{
		no_newline = 1;
		return ;
	}
	printf("%s", &str[i]);
	if (!no_newline)
		printf("\n");
}
