/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 14:40:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/11 14:54:02 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	builtin_pwd(void);

int	main(void)
{
	int	exit_status;

	printf("Testing pwd built-in:\n");
	printf("---------------------\n");
	exit_status = builtin_pwd();
	printf("Exit status: %d\n", exit_status);
	return (0);
}
