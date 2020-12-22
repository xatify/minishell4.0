/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 10:01:06 by abbouzid          #+#    #+#             */
/*   Updated: 2020/12/22 11:33:26 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		ft_strlen(char *str)
{
	int 	len;

	len = 0;
	if (str == 0)
		return (len);
	while(*str++)
		len++;
	return (len);
}

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
	while(index < len)
	{
		dst[index] = src[index];
		index++;
	}
}

int			ft_strcmp(char *str1, char *str2)
{
	int		i;

	i = 0;
	while (str1[i] && (str1[i] == str2[i]))
		i++;
	return (str1[i] - str2[i]);
}

void		*ft_memset(void	*b, int c, size_t len)
{
	unsigned char *ptr;

	ptr = (unsigned char *)b;
	while (len--)
		*ptr++ = (unsigned char)c;
	return (b);
}

bool	is_white_character(char c)
{
	return ((c == ' ' || c == '\t') ? TRUE: FALSE);
}