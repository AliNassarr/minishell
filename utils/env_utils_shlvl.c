/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_shlvl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 00:00:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/23 03:53:51 by alnassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_atoi_simple(const char *str)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			return (0);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

static char	*ft_itoa_simple(int n, t_head *gc)
{
	char	*str;
	int		len;
	int		temp;

	len = 1;
	temp = n;
	while (temp >= 10)
	{
		temp /= 10;
		len++;
	}
	str = gcmalloc(gc, len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}

void	increment_shlvl(char ***env, t_head *gc)
{
	char	*shlvl_str;
	int		shlvl;
	char	*new_shlvl;

	shlvl_str = get_env_value(*env, "SHLVL");
	if (shlvl_str)
		shlvl = ft_atoi_simple(shlvl_str);
	else
		shlvl = 0;
	shlvl++;
	new_shlvl = ft_itoa_simple(shlvl, gc);
	if (new_shlvl)
		*env = set_env_value(*env, "SHLVL", new_shlvl, gc);
}
