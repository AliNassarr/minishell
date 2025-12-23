/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 22:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/23 03:56:36 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../utils/ft_utils.h"
#include <limits.h>

char	*get_first_arg(const char *str, t_head *gc);
/*
** is_numeric - Check if string represents a valid number
** Allows: optional +/- prefix, digits only
*/
int		is_numeric(const char *str);

/*
** ft_atol - Convert string to long with overflow detection
** Returns: 1 on success (value stored in *result), 0 on overflow
*/
int		ft_atol(const char *str, long *result);
int		has_spaces(const char *str);

/*
** has_spaces - Check if string contains spaces (multiple args)
*/

/*
** builtin_exit - Exit the shell with optional exit code
**
** BEHAVIOR:
** - exit: Exit with last command status (shell->exit_status)
** - exit N: Exit with code N (0-255, wraps if > 255)
** - exit text: Error message, set exit_status=2, DON'T exit
** - exit 42 extra: Too many arguments, don't exit, return 1
**
** ALGORITHM:
** 1. Print "exit" to stderr (bash behavior)
** 2. If no arguments:
**    - Set shell->should_exit = 1
**    - Return shell->exit_status
** 3. If argument provided:
**    - Check if numeric (allow +/- prefix, spaces)
**    - If NOT numeric:
**      * Print: "exit: [arg]: numeric argument required"
**      * Set shell->exit_status = 2
**      * Set shell->should_exit = 1
**      * Return 2
**    - If too many arguments (more than 1 number):
**      * Print: "exit: too many arguments"
**      * Return 1 (DON'T exit in this case!)
**    - If valid number:
**      * Convert to int (handle overflow)
**      * Mod 256 to get valid exit code (0-255)
**      * Set shell->should_exit = 1
**      * Return exit_code
**
** EXAMPLES:
** $ exit           # Exit with $? (last status)
** $ exit 0         # Exit with code 0
** $ exit 42        # Exit with code 42
** $ exit 999       # Exit with code 231 (999 % 256)
** $ exit hello     # Error: numeric argument required (exits with 2)
** $ exit 1 2       # Error: too many arguments (DOESN'T exit!)
**
** HELPER FUNCTIONS NEEDED:
** - is_numeric(char *str): Check if string is valid number
** - ft_atoi(char *str): Convert string to integer
**
** RETURN:
** - Exit code (0-255) if exiting
** - 1 if too many arguments (no exit)
** - 2 if non-numeric argument (exits)
*/

int		handle_exit_args(t_shell *shell, char *args);
int		process_numeric_arg(t_shell *shell, char *args);

int	builtin_exit(t_shell *shell, char *args)
{
	int	ret;

	if (!args || args[0] == '\0')
	{
		shell->should_exit = 1;
		return (shell->exit_status);
	}
	ret = handle_exit_args(shell, args);
	if (ret != -1)
		return (ret);
	return (process_numeric_arg(shell, args));
}
