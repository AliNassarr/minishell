/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 00:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/24 21:13:42 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../utils/ft_utils.h"

void	update_pwd_env(t_shell *shell, char *cwd)
{
	if (getcwd(cwd, sizeof(char) * 1024) != NULL)
	{
		shell->pwd = ft_strdup_gc(cwd, shell->env_gc);
		shell->env = set_env_value(shell->env, "PWD", cwd, shell->env_gc);
		shell->env = set_env_value(shell->env, "OLDPWD", shell->oldpwd,
				shell->env_gc);
	}
}

char	*handle_oldpwd(t_shell *shell)
{
	if (!shell->oldpwd)
		return (printf("cd: OLDPWD not set\n"), NULL);
	printf("%s\n", shell->oldpwd);
	return (shell->oldpwd);
}

char	*handle_double_dash(t_shell *shell)
{
	char	*home;

	home = get_env_value(shell->env, "HOME");
	if (!home)
		return (printf("cd: HOME not set\n"), NULL);
	return (home);
}

char	*handle_invalid_option(char *path, int *error_code)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putendl_fd(": invalid option", 2);
	*error_code = 2;
	return (NULL);
}

char	*handle_home_or_tilde(t_shell *shell, char *path)
{
	char	*home;

	home = get_env_value(shell->env, "HOME");
	if (!home)
		return (printf("cd: HOME not set\n"), NULL);
	if (!path || path[0] == '\0')
		return (home);
	if (ft_strcmp(path, "~") == 0 || path[1] == '\0')
		return (home);
	return (ft_strjoin_gc(home, path + 1, shell->env_gc));
}
