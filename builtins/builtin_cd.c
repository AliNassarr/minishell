/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 10:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/22 23:48:42 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../utils/ft_utils.h"

static char	*get_cd_path(t_shell *shell, char *path, int *error_code)
{
	char	*home;

	*error_code = 1;
	if (!path || path[0] == '\0')
	{
		home = get_env_value(shell->env, "HOME");
		if (!home)
			return (printf("cd: HOME not set\n"), NULL);
		return (home);
	}
	if (ft_strcmp(path, "~") == 0 || ft_strncmp(path, "~/", 2) == 0)
	{
		home = get_env_value(shell->env, "HOME");
		if (!home)
			return (printf("cd: HOME not set\n"), NULL);
		if (path[1] == '\0')
			return (home);
		return (ft_strjoin_gc(home, path + 1, shell->env_gc));
	}
	if (ft_strcmp(path, "-") == 0)
	{
		if (!shell->oldpwd)
			return (printf("cd: OLDPWD not set\n"), NULL);
		printf("%s\n", shell->oldpwd);
		return (shell->oldpwd);
	}
	if (ft_strcmp(path, "--") == 0)
	{
		home = get_env_value(shell->env, "HOME");
		if (!home)
			return (printf("cd: HOME not set\n"), NULL);
		return (home);
	}
	if (path[0] == '-' && path[1] == '-' && path[2] == '-')
	{
		fprintf(stderr, "cd: %s: invalid option\n", path);
		*error_code = 2;
		return (NULL);
	}
	return (path);
}

int	builtin_cd(t_shell *shell, char *path, t_head *gc)
{
	char	*target;
	char	cwd[1024];
	int		error_code;

	(void)gc;
	target = get_cd_path(shell, path, &error_code);
	if (!target)
		return (error_code);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (perror("cd: getcwd"), 1);
	if (chdir(target) == -1)
		return (perror("cd"), 1);
	shell->oldpwd = ft_strdup_gc(cwd, shell->env_gc);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		shell->pwd = ft_strdup_gc(cwd, shell->env_gc);
		shell->env = set_env_value(shell->env, "PWD", cwd, shell->env_gc);
		shell->env = set_env_value(shell->env, "OLDPWD", shell->oldpwd,
			shell->env_gc);
	}
	return (0);
}
