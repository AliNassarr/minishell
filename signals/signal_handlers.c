/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/23 02:55:35 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

volatile sig_atomic_t	g_signal_flag = 0;

void	interactivehandler(int sig)
{
	(void)sig;
	g_signal_flag = SIGINT;
	write(1, "\n", 1);
}
