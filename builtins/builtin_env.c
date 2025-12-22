/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 20:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/22 23:48:42 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../utils/ft_utils.h"
#include <sys/wait.h>
#include <sys/stat.h>

static char	*find_in_path(char *cmd, char **env)
{
	char	*path_env;
	char	*path_copy;
	char	*dir;
	char	*full_path;
	int		i;
	struct stat	st;

	if (ft_strchr(cmd, '/'))
		return (cmd);
	path_env = get_env_value(env, "PATH");
	if (!path_env)
		return (NULL);
	path_copy = ft_strdup(path_env);
	if (!path_copy)
		return (NULL);
	dir = ft_strtok(path_copy, ":");
	while (dir)
	{
		i = ft_strlen(dir) + ft_strlen(cmd) + 2;
		full_path = malloc(i);
		if (full_path)
		{
			ft_strcpy(full_path, dir);
			ft_strcat(full_path, "/");
			ft_strcat(full_path, cmd);
			if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
			{
				free(path_copy);
				return (full_path);
			}
			free(full_path);
		}
		dir = ft_strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

int	builtin_env(t_shell *shell, char **args)
{
	int		i;
	pid_t	pid;
	int		status;
	char	*cmd_path;

	if (!args || !args[1])
	{
		i = 0;
		while (shell->env[i])
		{
			printf("%s\n", shell->env[i]);
			i++;
		}
		return (0);
	}
	cmd_path = find_in_path(args[1], shell->env);
	if (!cmd_path)
	{
		fprintf(stderr, "env: %s: No such file or directory\n", args[1]);
		return (127);
	}
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		execve(cmd_path, &args[1], shell->env);
		fprintf(stderr, "env: %s: No such file or directory\n", args[1]);
		exit(127);
	}
	if (cmd_path != args[1])
		free(cmd_path);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}