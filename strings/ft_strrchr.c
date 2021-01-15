/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 09:14:27 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/15 19:00:01 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*ptr;
	char	*pos;

	ptr = (char *)str;
	pos = 0;
	while (*ptr != '\0')
	{
		if (*ptr == (char)c)
			pos = ptr;
		ptr++;
	}
	if (c == '\0')
		return (ptr);
	return (pos);
}

char	*remove_quotes(char *value)
{
	char	*unquoted;
	int		i;

	i = ft_strlen(value) - 1;
	if (value[0] == value[i] && (value[0] == 0x27 || value[0] == 0x22))
	{
		if (!(unquoted = malloc(ft_strlen(value))))
			return (NULL);
		ft_strlcpy(unquoted, value + 1, i - 1);
		free(value);
		return (unquoted);
	}
	return (value);
}
