/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 00:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/23 03:35:41 by alnassar         ###   ########.fr       */
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
