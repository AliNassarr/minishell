/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_echo_v2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 15:45:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/11 16:33:58 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	builtin_echo_str(char **tokens, int count);

int	main(void)
{
	char	*test1[] = {"echo", "hello", "world"};
	char	*test2[] = {"echo", "-n", "hello", "world"};
	char	*test3[] = {"echo"};
	char	*test4[] = {"echo", "-n"};
	char	*test5[] = {"echo", "one", "two", "three"};

	printf("Test 1: echo hello world\n");
	printf("Output: ");
	builtin_echo_str(test1, 3);
	printf("---\n\n");
	printf("Test 2: echo -n hello world\n");
	printf("Output: ");
	builtin_echo_str(test2, 4);
	printf("[END]\n\n");
	printf("Test 3: echo (no args)\n");
	printf("Output: ");
	builtin_echo_str(test3, 1);
	printf("---\n\n");
	printf("Test 4: echo -n (only -n)\n");
	printf("Output: ");
	builtin_echo_str(test4, 2);
	printf("[END]\n\n");
	printf("Test 5: echo one two three\n");
	printf("Output: ");
	builtin_echo_str(test5, 4);
	printf("---\n");
	return (0);
}
