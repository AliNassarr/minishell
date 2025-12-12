/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 15:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/11 16:33:53 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	builtin_echo(char *str);

int	main(void)
{
	printf("Test 1: echo hello world\n");
	printf("Output: ");
	builtin_echo("hello world");
	printf("\n");
	
	printf("Test 2: echo -n hello world\n");
	printf("Output: ");
	builtin_echo("-n hello world");
	printf("[END]\n\n");
	
	printf("Test 3: echo (empty string)\n");
	printf("Output: ");
	builtin_echo("");
	printf("\n");
	
	printf("Test 4: echo -n (only -n)\n");
	printf("Output: ");
	builtin_echo("-n");
	printf("[END]\n\n");
	
	printf("Test 5: echo one two three\n");
	printf("Output: ");
	builtin_echo("one two three");
	
	return (0);
}
