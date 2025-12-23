/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_special.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 00:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/23 03:53:51 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	check_special_char(char c)
{
	if (c == '&' || c == '|' || c == '(' || c == ')')
		return (1);
	return (0);
}

static int	skip_to_value(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] != '=')
		return (-1);
	return (i + 1);
}

int	has_special_chars_in_value(const char *str)
{
	int		i;
	int		in_quotes;
	char	quote_char;

	i = skip_to_value(str);
	if (i == -1)
		return (0);
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
		else if (!in_quotes && check_special_char(str[i]))
			return (1);
		i++;
	}
	return (0);
}
