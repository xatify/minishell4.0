/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 10:01:06 by abbouzid          #+#    #+#             */
/*   Updated: 2021/02/02 15:10:57 by abbouzid         ###   ########.fr       */
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

char 	*ft_strdup(char *str)
{
	int 	len;
	char	*dup;

	len = ft_strlen(str);
	if (!(dup = (char *)malloc(len + 1)))
		return (NULL);
	ft_memset(dup, 0, len + 1);
	if(str)
		ft_strcpy(dup, str);
	return (dup);
}

char 	*ft_strnstr(const char *haystack,const char *needle, int *end_name)
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