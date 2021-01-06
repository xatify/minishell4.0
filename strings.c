/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 10:01:06 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/06 10:10:34 by abbouzid         ###   ########.fr       */
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

bool	is_alpha(char c)
{
	if ((c >= 0x41 && c <= 0x5a) || (c >= 0x61 && c <= 0x7a))
		return (TRUE);
	return (FALSE);
}

bool	is_num(char c)
{
	if (c >= 0x30 && c <= 0x39)
		return (TRUE);
	return (FALSE);
}

bool is_underscore(char c)
{
	return ((c == '_')? TRUE: FALSE);
}

bool    is_identifier(char *str)
{
    int i;

    i = -1;
    while (str[++i])
    {
        if (i == 0)
        {
            if (!(is_alpha(str[i]) || is_underscore(str[i])))
                break;
        }
        else
        {
            if (!(is_alpha(str[i]) || is_underscore(str[i]) || is_num(str[i])))
                break;
        }
    }
    return ((str[i] == '\0')? TRUE: FALSE);
}
