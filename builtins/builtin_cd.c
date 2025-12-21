/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 10:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/21 02:21:36 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../utils/ft_utils.h"

static char	*get_cd_path(t_shell *shell, char *path)
{
	char	*home;

	if (!path || path[0] == '\0' || ft_strcmp(path, "~") == 0)
	{
		home = get_env_value(shell->env, "HOME");
		if (!home)
			return (printf("cd: HOME not set\n"), NULL);
		return (home);
	}
	if (ft_strcmp(path, "-") == 0)
	{
		if (!shell->oldpwd)
			return (printf("cd: OLDPWD not set\n"), NULL);
		printf("%s\n", shell->oldpwd);
		return (shell->oldpwd);
	}
	return (path);
}

int	builtin_cd(t_shell *shell, char *path, t_head *gc)
{
	char	*target;
	char	cwd[1024];

	(void)gc;
	target = get_cd_path(shell, path);
	if (!target)
		return (1);
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
