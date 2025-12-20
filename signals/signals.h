/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/20 16:43:24 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** SIGNALS.H - Header file for signal handling in minishell
** 
** This header declares all the functions and variables needed for
** handling signals (like Ctrl+C and Ctrl+\) in the minishell program.
*/

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
# include <sys/types.h>

/*
** Global flag to track if a signal was received.
** This is declared as 'extern' because it's defined in signal_handlers.c
** and used in other files.
*/
extern volatile sig_atomic_t	g_signal_flag;

/*
** SIGNAL SETUP FUNCTIONS (defined in signal_setup.c)
*/

/* Set up signals for interactive mode (waiting for user input) */
void	setupinteractive(void);

/* Set up signals for command execution (when a command is running) */
void	setupexecution(void);

/* Restore default signal behavior (used in child processes) */
void	restoredefaults(void);

/*
** SIGNAL HANDLER FUNCTIONS (defined in signal_handlers.c)
*/

/* Handle Ctrl+C in interactive mode - clears line and shows new prompt */
void	interactivehandler(int sig);

/*
** SIGNAL UTILITY FUNCTIONS (defined in signal_utils.c)
*/

/* Check if a process was killed by a signal and return appropriate exit code */
int		checksignalstatus(int status);

/* Print a message when a process is killed by a signal (Ctrl+C or Ctrl+\) */
void	printsignalmsg(int signal_num);

#endif
