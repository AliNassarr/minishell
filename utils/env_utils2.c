/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 00:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/25 02:06:02 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "ft_utils.h"

int	env_array_size(char **env);

static char	*create_new_var(const char *key, const char *value, t_head *gc)
{
	char	*new_var;
	int		key_len;

	key_len = ft_strlen((char *)key);
	if (!value)
	{
		new_var = gcmalloc(gc, key_len + 1);
		if (!new_var)
			return (NULL);
		ft_strcpy(new_var, key);
		return (new_var);
	}
	new_var = gcmalloc(gc, key_len + ft_strlen((char *)value) + 2);
	if (!new_var)
		return (NULL);
	ft_strcpy(new_var, key);
	ft_strcpy(new_var + key_len, "=");
	ft_strcpy(new_var + key_len + 1, value);
	return (new_var);
}

static char	**add_new_env_var(char **env, const char *key,
		const char *value, t_head *gc)
{
	char	**new_env;
	char	*new_var;
	int		size;
	int		i;

	size = env_array_size(env);
	new_env = gcmalloc(gc, sizeof(char *) * (size + 2));
	if (!new_env)
		return (env);
	i = 0;
	while (i < size)
	{
		new_env[i] = env[i];
		i++;
	}
	new_var = create_new_var(key, value, gc);
	if (!new_var)
		return (env);
	new_env[i] = new_var;
	new_env[i + 1] = NULL;
	return (new_env);
}

char	**set_env_value(char **env, const char *key, const char *value,
		t_head *gc)
{
	char	*new_var;
	int		key_len;
	int		i;

	if (!key)
		return (env);
	key_len = ft_strlen((char *)key);
	i = 0;
	while (env && env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0
			&& (env[i][key_len] == '=' || env[i][key_len] == '\0'))
		{
			new_var = create_new_var(key, value, gc);
			if (!new_var)
				return (env);
			env[i] = new_var;
			return (env);
		}
		i++;
	}
	return (add_new_env_var(env, key, value, gc));
}
