/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 10:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/13 19:51:28 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_array_size(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

char	**copy_environment(char **envp, t_head *gc)
{
	char	**new_env;
	int		i;
	int		size;

	size = env_array_size(envp);
	new_env = gc_malloc(gc, sizeof(char *) * (size + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new_env[i] = gc_malloc(gc, ft_strlen(envp[i]) + 1);
		if (!new_env[i])
			return (NULL);
		ft_strcpy(new_env[i], envp[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}
