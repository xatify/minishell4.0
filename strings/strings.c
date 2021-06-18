/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 10:01:06 by abbouzid          #+#    #+#             */
/*   Updated: 2021/06/18 13:31:00 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strcpy(char *dst, char *src)
{
	if (!src)
		return (dst);
	while (*src)
		*dst++ = *src++;
	*dst = *src;
	return (dst);
}

void	ft_strlcpy(char *dst, char *src, int len)
{
	int		index;

	index = 0;
	while (index < len)
	{
		dst[index] = src[index];
		index++;
	}
}

int	ft_strcmp(char *str1, char *str2)
{
	int		i;

	i = 0;
	while (str1[i] && (str1[i] == str2[i]))
		i++;
	return (str1[i] - str2[i]);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)b;
	while (len--)
		*ptr++ = (unsigned char)c;
	return (b);
}

char	*ft_strdup(char *str)
{
	int		len;
	char	*dup;

	len = ft_strlen(str);
	dup = (char *)malloc(len + 1);
	if (!dup)
		return (NULL);
	ft_memset(dup, 0, len + 1);
	if (str)
		ft_strcpy(dup, str);
	return (dup);
}
