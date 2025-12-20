/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: invader <invader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/20 17:16:18 by invader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** This file sets up signal handlers for the minishell program.
** It configures how the shell responds to keyboard interrupts (Ctrl+C)
** and quit signals (Ctrl+\) in different modes.
*/

#define _POSIX_C_SOURCE 200809L
#include "signals.h"
#include <string.h>
#include <signal.h>

/*
** setupinteractive - Sets up signal handlers for interactive mode
** 
** This function configures how the shell handles signals when waiting
** for user input (interactive mode). When you press Ctrl+C, it will:
** - Clear the current line
** - Show a new prompt
** - NOT exit the shell
** 
** When you press Ctrl+\ (SIGQUIT), it will be ignored.
** 
** This is the normal behavior you expect when typing commands.
*/
void	setupinteractive(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	// Setup handler for Ctrl+C (SIGINT)
	memset(&sa_int, 0, sizeof(sa_int));       // Clear the structure
	sigemptyset(&sa_int.sa_mask);             // No signals blocked during handler
	sa_int.sa_flags = SA_RESTART;             // Restart interrupted system calls
	sa_int.sa_handler = interactivehandler;   // Use our custom handler
	sigaction(SIGINT, &sa_int, NULL);         // Apply the settings
	
	// Setup handler for Ctrl+\ (SIGQUIT) - just ignore it
	memset(&sa_quit, 0, sizeof(sa_quit));
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sa_quit.sa_handler = SIG_IGN;             // Ignore this signal
	sigaction(SIGQUIT, &sa_quit, NULL);
}

/*
** setupexecution - Sets up signal handlers during command execution
** 
** This function configures signals when a command is running.
** Both Ctrl+C and Ctrl+\ are ignored by the parent shell process.
** The child process (running the command) will handle these signals itself.
** 
** This prevents the shell from exiting when you press Ctrl+C
** while a command is running.
*/
void	setupexecution(void)
{
	struct sigaction	sa_ignore;

	// Ignore both SIGINT and SIGQUIT during command execution
	memset(&sa_ignore, 0, sizeof(sa_ignore));
	sigemptyset(&sa_ignore.sa_mask);
	sa_ignore.sa_flags = 0;
	sa_ignore.sa_handler = SIG_IGN;           // Ignore the signal
	sigaction(SIGINT, &sa_ignore, NULL);
	sigaction(SIGQUIT, &sa_ignore, NULL);
}

/*
** restoredefaults - Restores default signal behavior
** 
** This function resets signal handlers back to their default behavior.
** Used in child processes before executing commands, so commands
** behave normally (can be interrupted with Ctrl+C, etc.).
** 
** Without this, child processes would inherit the parent's signal settings.
*/
void	restoredefaults(void)
{
	struct sigaction	sa_default;

	// Restore default behavior for both signals
	memset(&sa_default, 0, sizeof(sa_default));
	sigemptyset(&sa_default.sa_mask);
	sa_default.sa_flags = 0;
	sa_default.sa_handler = SIG_DFL;          // Use default handler
	sigaction(SIGINT, &sa_default, NULL);
	sigaction(SIGQUIT, &sa_default, NULL);
}
