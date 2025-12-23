/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_dispatch_join.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 00:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/23 03:35:41 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../utils/ft_utils.h"

static int	calc_total_len(char **args)
{
	int	total_len;
	int	i;

	total_len = 0;
	i = 1;
	while (args[i])
	{
		total_len += ft_strlen(args[i]);
		if (args[i + 1])
			total_len++;
		i++;
	}
	return (total_len);
}

char	*join_args(char **args)
{
	char	*result;
	int		total_len;
	int		i;
	int		j;
	int		k;

	if (!args || !args[1])
		return (NULL);
	total_len = calc_total_len(args);
	result = malloc(total_len + 1);
	if (!result)
		return (NULL);
	i = 1;
	k = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
			result[k++] = args[i][j++];
		if (args[i + 1])
			result[k++] = ' ';
		i++;
	}
	result[k] = '\0';
	return (result);
}
