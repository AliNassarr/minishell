/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 14:40:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/22 23:48:42 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../utils/ft_utils.h"

int	builtin_pwd(char *args)
{
	char	cwd[1024];
	char	*pwd;
	int		i;

	if (args)
	{
		i = 0;
		while (args[i] && args[i] == ' ')
			i++;
		if (args[i] == '-')
		{
			if (args[i + 1] == '-' && (args[i + 2] == ' ' || args[i + 2] == '\0'))
			{
				// "--" or "-- something" is allowed (end of options)
			}
			else
			{
				fprintf(stderr, "pwd: %s: invalid option\n", args);
				return (2);
			}
		}
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		return (0);
	}
	pwd = getenv("PWD");
	if (pwd)
	{
		printf("%s\n", pwd);
		return (0);
	}
	perror("pwd");
	return (1);
}
