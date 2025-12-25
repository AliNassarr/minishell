/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 00:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/24 18:02:41 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"
#include "../utils/ft_utils.h"
#include "../signals/signals.h"
#include <stdlib.h>

typedef struct s_expand_data
{
	char	*line;
	char	**env;
	char	*result;
	int		*i;
	int		*j;
}	t_expand_data;

static char	*get_var_value(char *varname, char **env)
{
	extern volatile sig_atomic_t	g_signal;
	int								i;
	int								len;

	if (varname[0] == '?' && varname[1] == '\0')
		return (int_to_str((int)(g_signal >> 16)));
	len = ft_strlen(varname);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], varname, len) == 0 && env[i][len] == '=')
			return (ft_strdup(&env[i][len + 1]));
		i++;
	}
	return (ft_strdup(""));
}

static int	calc_expanded_len(char *line, char **env)
{
	int		len;
	int		i;
	char	varname[256];
	char	*value;

	len = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1]
			&& (line[i + 1] == '?' || is_var_char(line[i + 1])))
		{
			extract_varname(line, &i, varname);
			value = get_var_value(varname, env);
			len += ft_strlen(value);
			free(value);
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

static void	process_expansion(t_expand_data *data)
{
	char	varname[256];
	char	*value;

	extract_varname(data->line, data->i, varname);
	value = get_var_value(varname, data->env);
	ft_strcpy(&data->result[*(data->j)], value);
	*(data->j) += ft_strlen(value);
	free(value);
}

char	*expand_heredoc_line(char *line, char **env)
{
	char			*result;
	int				i;
	int				j;
	t_expand_data	data;

	result = malloc(calc_expanded_len(line, env) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	data = (t_expand_data){line, env, result, &i, &j};
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1]
			&& (line[i + 1] == '?' || is_var_char(line[i + 1])))
			process_expansion(&data);
		else
			result[j++] = line[i++];
	}
	result[j] = '\0';
	return (result);
}
