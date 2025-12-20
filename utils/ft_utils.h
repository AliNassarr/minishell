/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: invader <invader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 15:30:00 by alnassar          #+#    #+#             */
/*   Updated: 2025/12/20 16:28:51 by invader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_H
# define FT_UTILS_H

# include <stddef.h>

/* Forward declaration to avoid circular dependency */
typedef struct s_head	t_head;

int		ft_strcmp(const char *s1, const char *s2);
int		ft_strlen(char *str);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strdup(char *s);
char	*ft_strdup_gc(char *s, t_head *gc);

#endif
