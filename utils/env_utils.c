/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 20:10:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/23 02:08:27 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "ft_utils.h"

/*
** env_array_size - Count the number of environment variables
*/
int	env_array_size(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

/*
** copy_environment - Copy environment variables array
*/
char	**copy_environment(char **envp, t_head *gc)
{
	char	**new_env;
	int		size;
	int		i;

	size = env_array_size(envp);
	new_env = gcmalloc(gc, sizeof(char *) * (size + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new_env[i] = ft_strdup_gc(envp[i], gc);
		if (!new_env[i])
			return (NULL);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

/*
** get_env_value - Get value of environment variable by key
*/
char	*get_env_value(char **env, const char *key)
{
	int		i;
	int		key_len;
	char	*equals;

	if (!env || !key)
		return (NULL);
	key_len = ft_strlen((char *)key);
	i = 0;
	while (env[i])
	{
		equals = env[i];
		while (*equals && *equals != '=')
			equals++;
		if (*equals == '=' && (equals - env[i]) == key_len
			&& ft_strncmp(env[i], key, key_len) == 0)
			return (equals + 1);
		i++;
	}
	return (NULL);
}
