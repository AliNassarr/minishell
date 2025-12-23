/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_helpers2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 00:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/23 03:35:41 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../utils/ft_utils.h"

char	*check_path_dir(char *dir, char *cmd);

static char	*search_in_dirs(char *path_copy, char *cmd)
{
	char	*dir;
	char	*full_path;

	dir = ft_strtok(path_copy, ":");
	while (dir)
	{
		full_path = check_path_dir(dir, cmd);
		if (full_path)
		{
			free(path_copy);
			return (full_path);
		}
		dir = ft_strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

char	*find_in_path(char *cmd, char **env)
{
	char	*path_env;
	char	*path_copy;

	if (ft_strchr(cmd, '/'))
		return (cmd);
	path_env = get_env_value(env, "PATH");
	if (!path_env)
		return (NULL);
	path_copy = ft_strdup(path_env);
	if (!path_copy)
		return (NULL);
	return (search_in_dirs(path_copy, cmd));
}
