/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 15:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/14 21:55:07 by alnassar         ###   ########.fr       */
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
	if (ft_strcmp(str, "-n") == 0)
		return ;
	i = 0;
	while (str[i] == '-' && str[i + 1] == 'n' && str[i + 2] == ' ')
	{
		no_newline = 1;
		i += 3;
	}
	printf("%s", &str[i]);
	if (!no_newline)
		printf("\n");
}
