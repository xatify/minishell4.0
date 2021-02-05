/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 09:14:27 by abbouzid          #+#    #+#             */
/*   Updated: 2021/02/03 12:05:17 by keddib           ###   ########.fr       */
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

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t i;

	if (!src && !dst)
		return (NULL);
	i = 0;
	while (i < n)
	{
		*((char*)dst + i) = *((char*)src + i);
		i++;
	}
	return (dst);
}

char	*ft_strnstr(const char *haystack, const char *needle, int *end_name)
{
	char	*str;
	char	*sub;
	size_t	i;
	size_t	j;

	str = (char*)haystack;
	sub = (char*)needle;
	i = 0;
	if (*sub == 0)
		return (str);
	while (str[i] != '\0')
	{
		j = 0;
		while (str[i + j] == sub[j] && (i + j) < strlen(str))
		{
			j++;
			if (sub[j] == '\0')
			{
				*end_name = i;
				return (str + i + j);
			}
		}
		i++;
	}
	return (NULL);
}
