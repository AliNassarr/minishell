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
** ft_atoi_simple - Convert string to integer
*/
static int	ft_atoi_simple(const char *str)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

/*
** ft_itoa_simple - Convert integer to string
*/
static char	*ft_itoa_simple(int n, t_head *gc)
{
	char	buffer[12];
	int		i;
	int		len;
	char	*result;

	if (n == 0)
		return (ft_strdup_gc("0", gc));
	i = 0;
	while (n > 0)
	{
		buffer[i++] = (n % 10) + '0';
		n /= 10;
	}
	len = i;
	result = gcmalloc(gc, len + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (len > 0)
		result[i++] = buffer[--len];
	result[i] = '\0';
	return (result);
}

/*
** increment_shlvl - Increment SHLVL environment variable
*/
void	increment_shlvl(char ***env, t_head *gc)
{
	char	*shlvl_str;
	int		shlvl;
	char	*new_shlvl;

	shlvl_str = get_env_value(*env, "SHLVL");
	if (shlvl_str)
		shlvl = ft_atoi_simple(shlvl_str);
	else
		shlvl = 0;
	shlvl++;
	new_shlvl = ft_itoa_simple(shlvl, gc);
	if (new_shlvl)
		*env = set_env_value(*env, "SHLVL", new_shlvl, gc);
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

/*
** set_env_value - Set or update environment variable
*/
char	**set_env_value(char **env, const char *key, const char *value,
		t_head *gc)
{
	char	**new_env;
	int		i;
	int		size;
	char	*new_var;
	int		key_len;

	if (!key || !value)
		return (env);
	key_len = ft_strlen((char *)key);
	i = 0;
	while (env && env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
		{
			new_var = gcmalloc(gc, key_len + ft_strlen((char *)value) + 2);
			if (!new_var)
				return (env);
			ft_strcpy(new_var, key);
			ft_strcpy(new_var + key_len, "=");
			ft_strcpy(new_var + key_len + 1, value);
			env[i] = new_var;
			return (env);
		}
		i++;
	}
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
	new_var = gcmalloc(gc, key_len + ft_strlen((char *)value) + 2);
	if (!new_var)
		return (env);
	ft_strcpy(new_var, key);
	ft_strcpy(new_var + key_len, "=");
	ft_strcpy(new_var + key_len + 1, value);
	new_env[i] = new_var;
	new_env[i + 1] = NULL;
	return (new_env);
}

/*
** unset_env_value - Remove environment variable
*/
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
