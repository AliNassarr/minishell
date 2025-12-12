/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 15:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/11 16:04:21 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_utils.h"

void	builtin_echo(char *str)
{
	int i = 0;
    if  (ft_strlen(str) >= 3 &&
        str[i] == '-' && str[i + 1] == 'n' && str[i + 2] == ' ')
        i += 3;
    if (ft_strlen(str) == 2 && str[i] == '-' && str[i + 1] == 'n')
        return;
    printf("%s", str + i);
    if (i == 0)
        printf("\n");
}
