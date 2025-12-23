/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 04:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/23 04:04:07 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"
#include <string.h>

char	**extract_command(t_parse_token *tokens, int count, t_head *head)
{
	char	**cmd_array;
	int		i;
	int		j;

	cmd_array = gcmalloc(head, sizeof(char *) * (count + 1));
	if (!cmd_array)
		return (NULL);
	i = 0;
	j = 0;
	while (i < count)
	{
		if ((tokens[i].type == CMD || tokens[i].type == ARG)
			&& tokens[i].str && tokens[i].str[0] != '\0')
		{
			cmd_array[j] = tokens[i].str;
			j++;
		}
		i++;
	}
	cmd_array[j] = NULL;
	return (cmd_array);
}

static char	*search_in_path(char *cmd, char *path_env)
{
	char	*path_copy;
	char	*dir;
	char	*full_path;

	path_copy = strdup(path_env);
	if (!path_copy)
		return (NULL);
	dir = strtok(path_copy, ":");
	while (dir)
	{
		full_path = malloc(strlen(dir) + strlen(cmd) + 2);
		if (full_path)
		{
			strcpy(full_path, dir);
			strcat(full_path, "/");
			strcat(full_path, cmd);
			if (access(full_path, X_OK) == 0)
				return (free(path_copy), full_path);
			free(full_path);
		}
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

char	*find_command_path(char *cmd, char **env)
{
	int		i;

	if (!cmd || cmd[0] == '/' || cmd[0] == '.')
		return (cmd);
	i = 0;
	while (env && env[i])
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
			return (search_in_path(cmd, env[i] + 5));
		i++;
	}
	return (cmd);
}
