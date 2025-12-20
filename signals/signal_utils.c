/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/20 16:43:24 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** This file contains utility functions for handling signals after
** a child process has finished executing.
*/

#include "signals.h"
#include <sys/wait.h>
#include <unistd.h>

/*
** checksignalstatus - Check if a process was killed by a signal
** 
** After a command finishes, this function checks how it ended:
** - If it was killed by a signal (like Ctrl+C), it prints a message
**   and returns 128 + signal_number (standard shell convention)
** - If it exited normally, it returns the exit code
** 
** This is important for setting the $? variable correctly.
** 
** @param status: The status value from wait() or waitpid()
** @return: The exit code to set (0-255 for normal exit, 128+ for signals)
*/
int	checksignalstatus(int status)
{
	int	signal_num;

	// Check if the process was terminated by a signal
	if (WIFSIGNALED(status))
	{
		signal_num = WTERMSIG(status);        // Get which signal killed it
		printsignalmsg(signal_num);           // Print appropriate message
		return (128 + signal_num);            // Return 128 + signal number
	}
	// Process exited normally
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));         // Return the exit code
	return (0);
}

/*
** printsignalmsg - Print a message when a process is killed by a signal
** 
** This function prints user-friendly messages when a command is
** terminated by a signal:
** - SIGINT (Ctrl+C): Just prints a newline
** - SIGQUIT (Ctrl+\): Prints "Quit (core dumped)"
** 
** This mimics the behavior of bash and other shells.
** 
** @param signal_num: The signal number that killed the process
*/
void	printsignalmsg(int signal_num)
{
	if (signal_num == SIGINT)
		write(1, "\n", 1);                    // Ctrl+C: just newline
	else if (signal_num == SIGQUIT)
		write(1, "Quit (core dumped)\n", 19);  // Ctrl+\: show quit message
}
