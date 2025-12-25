/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 10:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/24 21:13:42 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../utils/ft_utils.h"

char	*handle_home_or_tilde(t_shell *shell, char *path);
char	*handle_oldpwd(t_shell *shell);
char	*handle_double_dash(t_shell *shell);
char	*handle_invalid_option(char *path, int *error_code);

static char	*get_cd_path(t_shell *shell, char *path, int *error_code)
{
	*error_code = 1;
	if (!path || path[0] == '\0' || ft_strcmp(path, "~") == 0
		|| ft_strncmp(path, "~/", 2) == 0)
		return (handle_home_or_tilde(shell, path));
	if (ft_strcmp(path, "-") == 0)
		return (handle_oldpwd(shell));
	if (ft_strcmp(path, "--") == 0)
		return (handle_double_dash(shell));
	if (path[0] == '-' && path[1] == '-' && path[2] == '-')
		return (handle_invalid_option(path, error_code));
	return (path);
}

void	update_pwd_env(t_shell *shell, char *cwd);

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
	update_pwd_env(shell, cwd);
	return (0);
}
