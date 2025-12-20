/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: invader <invader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 23:43:39 by invader           #+#    #+#             */
/*   Updated: 2025/12/20 03:34:20 by invader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	whitespacecheck(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '\0')
		return (0);
	return (1);
}

void	startminishell(char *str)
{
	char		*fixed;
	char		**pp;
	t_treenode	*node;
	t_head		*head;

	head = intializehead();
	if (!head)
		return ;
	pp = NULL;
	if (!quotecheck(str))
	{
		printf("problem in quote");
		return ;
	}
	fixed = fixspaces(str, head, 0, 0);
	if (!fixed)
		return ;
	node = asthelper(fixed, head, pp);
	if (!node)
		return ;
	printf("test");
	print_ast(node);
}

int	main(int argc, char **argv, char **envp)
{
	char		*str;

	(void)envp;
	(void)argv;
	if (argc != 1)
		return (0);
	while (42)
	{
		str = readline("thisisit: ");
		if (!str)
			break ;
		if (str[0] && !whitespacecheck(str))
			add_history(str);
		startminishell(str);
		free(str);
	}
	printf("gg\n");
	rl_clear_history();
	return (0);
}
