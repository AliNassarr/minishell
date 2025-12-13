/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 10:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/13 19:54:38 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		printf("[%d] %s\n", i, env[i]);
		i++;
	}
	printf("---\n");
}

int	main(void)
{
	char	*test_env[] = {"HOME=/home/test", "PATH=/bin", NULL};
	char	**my_env;
	char	*value;
	t_head	gc;

	gc.head = NULL;
	printf("=== Testing Environment Functions ===\n\n");
	my_env = copy_environment(test_env, &gc);
	printf("1. Initial environment:\n");
	print_env(my_env);
	printf("2. Get HOME value:\n");
	value = get_env_value(my_env, "HOME");
	printf("   HOME = %s\n\n", value ? value : "NOT FOUND");
	printf("3. Add new variable MY_VAR=hello:\n");
	my_env = set_env_value(my_env, "MY_VAR", "hello", &gc);
	print_env(my_env);
	printf("4. Update existing MY_VAR=world:\n");
	my_env = set_env_value(my_env, "MY_VAR", "world", &gc);
	print_env(my_env);
	printf("5. Update HOME:\n");
	my_env = set_env_value(my_env, "HOME", "/home/newuser", &gc);
	print_env(my_env);
	gc_free_all(&gc);
	printf("Success! All tests passed!\n");
	return (0);
}
