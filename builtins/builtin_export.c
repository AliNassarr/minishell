/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 22:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/23 03:57:15 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../utils/ft_utils.h"

char	*extract_key(const char *str, int equals_pos, t_head *gc);
/*
** is_valid_identifier - Check if variable name is valid
** 
** Rules:
** - Must start with letter or underscore
** - Can contain letters, digits, underscores
** - Cannot be empty
*/
int		is_valid_identifier(const char *str);

/*
** parse_export_arg - Split "KEY=VALUE" into key and value
**
** Returns: index of '=' character, or -1 if no '=' found
*/
int		find_equals_sign(const char *str);

/*
** print_export - Print all env vars in "declare -x" format
*/
static void	print_export(t_shell *shell)
{
	int		i;
	int		j;
	char	*equals;

	i = 0;
	while (shell->env[i])
	{
		printf("declare -x ");
		j = 0;
		while (shell->env[i][j] && shell->env[i][j] != '=')
		{
			printf("%c", shell->env[i][j]);
			j++;
		}
		equals = &shell->env[i][j];
		if (*equals == '=')
			printf("=\"%s\"", equals + 1);
		printf("\n");
		i++;
	}
}

/*
** builtin_export - Add or modify environment variables
**
** BEHAVIOR:
** - export (no args): Print all env vars in format: declare -x KEY="VALUE"
** - export VAR=value: Add/update VAR in shell->env
** - export VAR: Mark VAR as exported (if exists)
**
** ALGORITHM:
** 1. If no arguments:
**    - Loop through shell->env
**    - Print each in format: declare -x KEY="VALUE"
**    - Sort alphabetically (bonus)
**
** 2. If arguments provided:
**    - Parse "KEY=VALUE" or just "KEY"
**    - Validate KEY (alphanumeric + underscore, no digit first)
**    - If invalid: print error, return 1
**    - Call set_env_value(shell->env, KEY, VALUE, gc)
**    - Update shell->env with returned array
**
** VALIDATION:
** - Valid:   export MY_VAR=hello, export _VAR=test, export VAR123=x
** - Invalid: export 123VAR=x, export MY-VAR=x, export MY.VAR=x
**
** EXAMPLES:
** $ export MY_VAR=hello
** $ export PATH=$PATH:/new/path   # Note: expansion needed in Stage 2
** $ export                         # List all variables
**
** RETURN:
** - 0 on success
** - 1 on error (invalid identifier)
*/

/*
** has_special_chars_in_value - Check if value contains special chars
** that would cause syntax errors: &, |, (, )
*/
int		has_special_chars_in_value(const char *str);

int		process_export_arg(t_shell *shell, char *str);

int	builtin_export(t_shell *shell, char *str, t_head *gc)
{
	(void)gc;
	if (!str || str[0] == '\0')
	{
		print_export(shell);
		return (0);
	}
	return (process_export_arg(shell, str));
}
