/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 11:44:48 by abbouzid          #+#    #+#             */
/*   Updated: 2019/10/14 21:19:15 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char *ptr1;
	unsigned char *ptr2;

	ptr1 = dst;
	ptr2 = (unsigned char *)src;
	while (n--)
	{
		if (*ptr2 == (unsigned char)c)
		{
			*ptr1 = *ptr2;
			return (++ptr1);
		}
		*ptr1++ = *ptr2++;
	}
	return (0);
}
