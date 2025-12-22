/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 22:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/22 23:48:42 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../utils/ft_utils.h"

/*
** is_valid_identifier - Check if variable name is valid
** 
** Rules:
** - Must start with letter or underscore
** - Can contain letters, digits, underscores
** - Cannot be empty
*/
static int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (str[0] != '_' && (str[0] < 'a' || str[0] > 'z')
		&& (str[0] < 'A' || str[0] > 'Z'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
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
** parse_export_arg - Split "KEY=VALUE" into key and value
**
** Returns: index of '=' character, or -1 if no '=' found
*/
static int	find_equals_sign(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

/*
** extract_key - Extract key from "KEY=VALUE"
*/
static char	*extract_key(const char *str, int equals_pos, t_head *gc)
{
	char	*key;
	int		i;

	key = gcmalloc(gc, equals_pos + 1);
	if (!key)
		return (NULL);
	i = 0;
	while (i < equals_pos)
	{
		key[i] = str[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

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
static int	has_special_chars_in_value(const char *str)
{
	int	i;
	int	in_quotes;
	char	quote_char;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] != '=')
		return (0);
	i++;
	in_quotes = 0;
	quote_char = 0;
	while (str[i])
	{
		if (!in_quotes && (str[i] == '"' || str[i] == '\''))
		{
			in_quotes = 1;
			quote_char = str[i];
		}
		else if (in_quotes && str[i] == quote_char)
			in_quotes = 0;
		else if (!in_quotes && (str[i] == '&' || str[i] == '|'
			|| str[i] == '(' || str[i] == ')'))
			return (1);
		i++;
	}
	return (0);
}

int	builtin_export(t_shell *shell, char *str, t_head *gc)
{
	int		equals_pos;
	char	*key;
	char	*value;

	(void)gc;
	if (!str || str[0] == '\0')
	{
		print_export(shell);
		return (0);
	}
	if (str[0] == '-')
	{
		fprintf(stderr, "export: %s: invalid option\n", str);
		return (2);
	}
	if (has_special_chars_in_value(str))
	{
		fprintf(stderr, "export: `%s': not a valid identifier\n", str);
		return (2);
	}
	if (!is_valid_identifier(str))
	{
		fprintf(stderr, "export: `%s': not a valid identifier\n", str);
		return (1);
	}
	equals_pos = find_equals_sign(str);
	if (equals_pos == -1)
		return (0);
	key = extract_key(str, equals_pos, shell->env_gc);
	if (!key)
		return (1);
	value = &str[equals_pos + 1];
	shell->env = set_env_value(shell->env, key, value,
		shell->env_gc);
	return (0);
}
