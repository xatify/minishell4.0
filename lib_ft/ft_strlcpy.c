/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 12:36:26 by abbouzid          #+#    #+#             */
/*   Updated: 2019/10/19 13:28:20 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t len;
	size_t i;

	i = 0;
	len = ft_strlen(src);
	while (*src && i < size - 1 && size != 0)
	{
		*(unsigned char *)dst++ = *(unsigned char *)src++;
		i++;
	}
	if (size != 0)
		*dst = '\0';
	return (len);
}
