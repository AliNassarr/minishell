/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 22:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/16 03:25:27 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../utils/ft_utils.h"

/*
** is_valid_unset_identifier - Check if variable name is valid
** 
** Similar to export validation but doesn't expect '='
*/
static int	is_valid_unset_identifier(const char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (str[0] != '_' && (str[0] < 'a' || str[0] > 'z')
		&& (str[0] < 'A' || str[0] > 'Z'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != '_' && (str[i] < 'a' || str[i] > 'z')
			&& (str[i] < 'A' || str[i] > 'Z')
			&& (str[i] < '0' || str[i] > '9'))
			return (0);
		i++;
	}
	return (1);
}

/*
** builtin_unset - Remove environment variables
**
** BEHAVIOR:
** - Removes one or more environment variables from shell->env
** - Does not print error if variable doesn't exist (bash behavior)
** - Cannot unset certain variables (PATH, PWD, etc. - optional protection)
**
** ALGORITHM:
** 1. Parse argument (can have multiple: unset VAR1 VAR2 VAR3)
** 2. For each variable name:
**    - Validate name (alphanumeric + underscore)
**    - Call unset_env_value(shell->env, VAR_NAME)
**    - Update shell->env with returned array
** 3. Return 0 (always successful, even if var didn't exist)
**
** VALIDATION:
** - Valid:   unset MY_VAR, unset _VAR, unset VAR123
** - Invalid: unset MY-VAR, unset 123VAR
**
** EXAMPLES:
** $ export MY_VAR=hello
** $ unset MY_VAR
** $ echo $MY_VAR       # Empty (variable removed)
** $ unset NONEXISTENT  # No error, just ignored
**
** IMPORTANT:
** - Use unset_env_value() from env_operations.c
** - That function handles memory management (creates new array without VAR)
** - Don't manually free - GC handles cleanup
**
** RETURN:
** - 0 on success (or if variable didn't exist)
** - 1 on error (invalid identifier)
*/

int	builtin_unset(t_shell *shell, char *str, t_head *gc)
{
	if (!str || str[0] == '\0')
		return (0);
	if (!is_valid_unset_identifier(str))
	{
		printf("unset: `%s': not a valid identifier\n", str);
		return (1);
	}
	shell->env = unset_env_value(shell->env, str, gc);
	return (0);
}
