/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: invader <invader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/20 17:16:19 by invader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** This file contains the actual signal handler functions.
** These are the functions that get called when a signal is received.
*/

#include "signals.h"
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

/*
** g_signal_flag - Global variable to track received signals
** 
** This is a special global variable that can be safely used in signal handlers.
** The 'volatile sig_atomic_t' type ensures it can be safely accessed
** from both the main program and signal handlers.
** 
** When a signal is received, this flag is set to the signal number,
** allowing the main program to check if a signal occurred.
*/
volatile sig_atomic_t	g_signal_flag = 0;

/*
** interactivehandler - Handler for Ctrl+C in interactive mode
** 
** This function is called when the user presses Ctrl+C while the shell
** is waiting for input. It:
** 1. Sets the global flag to indicate SIGINT was received
** 2. Prints a newline (moves to next line)
** 3. Clears the current input line
** 4. Shows a fresh prompt
** 
** This gives the user a clean line to type a new command without
** exiting the shell.
** 
** @param sig: The signal number (SIGINT in this case)
*/
void	interactivehandler(int sig)
{
	(void)sig;                    // We don't need the signal number
	g_signal_flag = SIGINT;       // Set flag to indicate Ctrl+C was pressed
	write(1, "\n", 1);            // Print newline (safe function to use in handler)
	rl_on_new_line();             // Tell readline we're on a new line
	rl_replace_line("", 0);       // Clear the current input line
	rl_redisplay();               // Show the prompt again
}
