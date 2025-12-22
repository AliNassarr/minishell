/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 22:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/22 23:48:42 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../utils/ft_utils.h"
#include <limits.h>

/*
** is_numeric - Check if string represents a valid number
** Allows: optional +/- prefix, digits only
*/
static int	is_numeric(const char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

/*
** ft_atol - Convert string to long with overflow detection
** Returns: 1 on success (value stored in *result), 0 on overflow
*/
static int	ft_atol(const char *str, long *result)
{
	long	num;
	long	sign;
	int		i;

	num = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (sign == 1 && num > (LONG_MAX - (str[i] - '0')) / 10)
			return (0);
		if (sign == -1 && (unsigned long)num > ((unsigned long)LONG_MAX + 1 - (str[i] - '0')) / 10)
			return (0);
		num = num * 10 + (str[i] - '0');
		i++;
	}
	*result = num * sign;
	return (1);
}

/*
** has_spaces - Check if string contains spaces (multiple args)
*/
static int	has_spaces(const char *str)
{
	int	i;
	int	in_quote;
	char	quote_char;

	i = 0;
	in_quote = 0;
	quote_char = 0;
	while (str[i])
	{
		if (!in_quote && (str[i] == '"' || str[i] == '\''))
		{
			in_quote = 1;
			quote_char = str[i];
		}
		else if (in_quote && str[i] == quote_char)
			in_quote = 0;
		else if (!in_quote && str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

/*
** get_first_arg - Extract first argument before space
*/
static char	*get_first_arg(const char *str, t_head *gc)
{
	int		i;
	char	*result;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	result = gcmalloc(gc, i + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != ' ')
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

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

int	builtin_exit(t_shell *shell, char *args)
{
	long	exit_code;
	int		final_code;
	char	*first_arg;
	t_head	*gc;

	// fprintf(stderr, "exit\n");
	if (!args || args[0] == '\0')
	{
		shell->should_exit = 1;
		return (shell->exit_status);
	}
	if (has_spaces(args))
	{
		gc = intializehead();
		first_arg = get_first_arg(args, gc);
		if (!is_numeric(first_arg))
		{
			fprintf(stderr, "exit: %s: numeric argument required\n", first_arg);
			shell->exit_status = 2;
			shell->should_exit = 1;
			gcallfree(gc);
			return (2);
		}
		gcallfree(gc);
		fprintf(stderr, "exit: too many arguments\n");
		return (1);
	}
	if (!is_numeric(args))
	{
		fprintf(stderr, "exit: %s: numeric argument required\n", args);
		shell->exit_status = 2;
		shell->should_exit = 1;
		return (2);
	}
	if (!ft_atol(args, &exit_code))
	{
		fprintf(stderr, "exit: %s: numeric argument required\n", args);
		shell->exit_status = 2;
		shell->should_exit = 1;
		return (2);
	}
	final_code = (int)((exit_code % 256 + 256) % 256);
	shell->should_exit = 1;
	return (final_code);
}
