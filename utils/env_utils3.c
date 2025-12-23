/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 00:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/23 03:35:41 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "ft_utils.h"

int	env_array_size(char **env);

char	**unset_env_value(char **env, const char *key, t_head *gc)
{
	char	**new_env;
	int		i;
	int		j;
	int		key_len;
	int		size;

	if (!env || !key)
		return (env);
	key_len = ft_strlen((char *)key);
	size = env_array_size(env);
	new_env = gcmalloc(gc, sizeof(char *) * (size + 1));
	if (!new_env)
		return (env);
	i = 0;
	j = 0;
	while (env[i])
	{
		if (!(ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '='))
			new_env[j++] = env[i];
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}
