/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/24 16:49:40 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include <sys/wait.h>
#include <unistd.h>

int	checksignalstatus(int status)
{
	int	signal_num;

	if (WIFSIGNALED(status))
	{
		signal_num = WTERMSIG(status);
		printsignalmsg(signal_num);
		return (128 + signal_num);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

void	printsignalmsg(int signal_num)
{
	if (!(g_signal & 0x100))
		return ;
	if (signal_num == SIGINT)
		write(1, "\n", 1);
}
