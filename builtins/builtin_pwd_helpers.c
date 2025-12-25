/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 00:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/24 21:13:42 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_pwd_options(char *args)
{
	int	i;

	if (!args)
		return (0);
	i = 0;
	while (args[i] && args[i] == ' ')
		i++;
	if (args[i] == '-')
	{
		if (args[i + 1] == '-' && (args[i + 2] == ' '
				|| args[i + 2] == '\0'))
			return (0);
		ft_putstr_fd("pwd: ", 2);
		ft_putstr_fd(args, 2);
		ft_putendl_fd(": invalid option", 2);
		return (2);
	}
	return (0);
}

int	print_pwd(void)
{
	char	cwd[1024];
	char	*pwd;

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
