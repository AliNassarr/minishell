/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_dispatch_helpers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 00:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/23 03:35:41 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../utils/ft_utils.h"

static int	handle_export(t_shell *shell, char **args)
{
	t_head	*gc;
	int		ret;
	int		i;

	gc = intializehead();
	if (!args[1])
		ret = builtin_export(shell, NULL, gc);
	else
	{
		i = 1;
		ret = 0;
		while (args[i])
			ret |= builtin_export(shell, args[i++], gc);
	}
	gcallfree(gc);
	return (ret);
}

static int	handle_unset(t_shell *shell, char **args)
{
	t_head	*gc;
	int		ret;
	int		i;

	gc = intializehead();
	i = 1;
	ret = 0;
	while (args[i])
		ret |= builtin_unset(shell, args[i++], gc);
	gcallfree(gc);
	return (ret);
}

static int	handle_cd(t_shell *shell, char *joined_args)
{
	t_head	*gc;
	int		ret;

	gc = intializehead();
	ret = builtin_cd(shell, joined_args, gc);
	gcallfree(gc);
	return (ret);
}

int	dispatch_builtin(t_shell *shell, char *cmd, char **args, char *joined)
{
	int	ret;

	ret = 0;
	if (ft_strcmp(cmd, ":") == 0)
		ret = 0;
	else if (ft_strcmp(cmd, "echo") == 0)
		ret = (builtin_echo(joined), 0);
	else if (ft_strcmp(cmd, "cd") == 0)
		ret = handle_cd(shell, joined);
	else if (ft_strcmp(cmd, "pwd") == 0)
		ret = builtin_pwd(joined);
	else if (ft_strcmp(cmd, "export") == 0)
		ret = handle_export(shell, args);
	else if (ft_strcmp(cmd, "unset") == 0)
		ret = handle_unset(shell, args);
	else if (ft_strcmp(cmd, "env") == 0)
		ret = builtin_env(shell, args);
	else if (ft_strcmp(cmd, "exit") == 0)
	{
		ret = builtin_exit(shell, joined);
		shell->exit_status = ret;
	}
	else
		ret = 1;
	return (ret);
}
