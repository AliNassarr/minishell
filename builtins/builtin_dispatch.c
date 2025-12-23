/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_dispatch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 20:15:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/23 03:35:41 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../utils/ft_utils.h"

/*
** is_builtin - Check if command is a builtin
*/
int	is_builtin(const char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, ":") == 0)
		return (1);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

/*
** join_args - Join command arguments into a single string
** Returns: Joined string with arguments separated by spaces (must be freed)
*/
char	*join_args(char **args);

/*
** execute_builtin - Execute a builtin command
** Returns: Exit status
*/
int	execute_builtin(t_shell *shell, char *cmd, char **args)
{
	char	*joined_args;
	int		ret;

	joined_args = join_args(args);
	ret = dispatch_builtin(shell, cmd, args, joined_args);
	if (joined_args)
		free(joined_args);
	return (ret);
}
