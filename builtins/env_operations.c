/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 10:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/13 19:51:48 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	*get_env_value(char **env, const char *key)
{
	int		i;
	int		key_len;

	if (!env || !key)
		return (NULL);
	key_len = ft_strlen((char *)key);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0
			&& env[i][key_len] == '=')
			return (env[i] + key_len + 1);
		i++;
	}
	return (NULL);
}

static char	*build_env_string(const char *key, const char *value, t_head *gc)
{
	char	*result;
	int		key_len;
	int		val_len;
	int		i;
	int		j;

	key_len = ft_strlen((char *)key);
	val_len = ft_strlen((char *)value);
	result = gc_malloc(gc, key_len + val_len + 2);
	if (!result)
		return (NULL);
	i = 0;
	while (i < key_len)
	{
		result[i] = key[i];
		i++;
	}
	result[i++] = '=';
	j = 0;
	while (j < val_len)
		result[i++] = value[j++];
	result[i] = '\0';
	return (result);
}

static int	find_env_index(char **env, const char *key)
{
	int	i;
	int	key_len;

	if (!env || !key)
		return (-1);
	key_len = ft_strlen((char *)key);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0
			&& env[i][key_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	**set_env_value(char **env, const char *key, const char *value,
		t_head *gc)
{
	char	**new_env;
	char	*new_entry;
	int		index;
	int		size;

	if (!key || !value)
		return (env);
	new_entry = build_env_string(key, value, gc);
	if (!new_entry)
		return (env);
	index = find_env_index(env, key);
	if (index >= 0)
	{
		env[index] = new_entry;
		return (env);
	}
	size = env_array_size(env);
	new_env = gc_malloc(gc, sizeof(char *) * (size + 2));
	if (!new_env)
		return (env);
	size = 0;
	while (env[size])
	{
		new_env[size] = env[size];
		size++;
	}
	new_env[size] = new_entry;
	new_env[size + 1] = NULL;
	return (new_env);
}
