/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 00:00:00 by alnassar         #+#    #+#             */
/*   Updated: 2025/12/24 00:00:00 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"
#include "../utils/ft_utils.h"
#include <signal.h>
#include <stdlib.h>

static void	copy_exit_status(char *expanded, int *j)
{
	char							*exit_status_str;
	extern volatile sig_atomic_t	g_signal;
	int								k;

	exit_status_str = ft_itoa((int)(g_signal >> 16));
	if (!exit_status_str)
		return ;
	k = 0;
	while (exit_status_str[k])
		expanded[(*j)++] = exit_status_str[k++];
	free(exit_status_str);
}

static void	copy_variable(char *variable, char *expanded, int *j)
{
	int	k;

	k = 0;
	while (variable[k])
		expanded[(*j)++] = variable[k++];
}

void	mimic_variable(char *varname, char *expanded, int *j, char **pp)
{
	char	*variable;

	if (varname[0] == '?' && varname[1] == '\0')
	{
		copy_exit_status(expanded, j);
		return ;
	}
	variable = inpp(varname, pp);
	if (variable)
	{
		copy_variable(variable, expanded, j);
		return ;
	}
	variable = getenv(varname);
	if (variable)
		copy_variable(variable, expanded, j);
}

void	expand_loop(char *str, char *expanded, char **pp)
{
	int		i;
	int		j;
	char	varname[1024];

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			getname(str, &i, varname);
			mimic(varname, expanded, &j, pp);
		}
		else if (str[i] == '$' && str[i + 1] && !isdelimeter(str[i + 1]))
		{
			getname(str, &i, varname);
			mimic(varname, expanded, &j, pp);
		}
		else
			expanded[j++] = str[i++];
	}
	expanded[j] = '\0';
}

void	expansion_process(t_token *tokens, int count, char **pp, t_head *head)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (tokens[i].expansion == 1)
		{
			tokens[i].str = expand(head, tokens[i].str, pp);
			if (!tokens[i].str)
				return ;
		}
		i++;
	}
}
