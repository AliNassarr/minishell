/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_dispatch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 20:15:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/20 21:37:18 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../utils/ft_utils.h"
#include "../utils/ft_utils.h"

/*
** is_builtin - Check if command is a builtin
*/
int	is_builtin(const char *cmd)
{
	if (!cmd)
		return (0);
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
char	*join_args(char **args)
{
	char	*result;
	int		total_len;
	int		i;
	int		j;
	int		k;

	if (!args || !args[1])
		return (NULL);
	total_len = 0;
	i = 1;
	while (args[i])
	{
		total_len += ft_strlen(args[i]);
		if (args[i + 1])
			total_len++;
		i++;
	}
	result = malloc(total_len + 1);
	if (!result)
		return (NULL);
	i = 1;
	k = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
			result[k++] = args[i][j++];
		if (args[i + 1])
			result[k++] = ' ';
		i++;
	}
	result[k] = '\0';
	return (result);
}

/*
** execute_builtin - Execute a builtin command
** Returns: Exit status
*/
int	execute_builtin(t_shell *shell, char *cmd, char **args)
{
	char	*joined_args;
	int		ret;

	joined_args = join_args(args);
	ret = 0;
	if (ft_strcmp(cmd, "echo") == 0)
		builtin_echo(joined_args);
	else if (ft_strcmp(cmd, "cd") == 0)
	{
		t_head *gc = intializehead();
		ret = builtin_cd(shell, joined_args, gc);
		gcallfree(gc);
	}
	else if (ft_strcmp(cmd, "pwd") == 0)
		ret = builtin_pwd();
	else if (ft_strcmp(cmd, "export") == 0)
	{
		t_head *gc = intializehead();
		ret = builtin_export(shell, joined_args, gc);
		gcallfree(gc);
	}
	else if (ft_strcmp(cmd, "unset") == 0)
	{
		t_head *gc = intializehead();
		ret = builtin_unset(shell, joined_args, gc);
		gcallfree(gc);
	}
	else if (ft_strcmp(cmd, "env") == 0)
		ret = builtin_env(shell);
	else if (ft_strcmp(cmd, "exit") == 0)
		ret = builtin_exit(shell, joined_args);
	else
		ret = 1;
	if (joined_args)
		free(joined_args);
	return (ret);
}
