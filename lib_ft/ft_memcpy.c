/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 10:51:47 by abbouzid          #+#    #+#             */
/*   Updated: 2019/10/14 19:45:21 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char *ptr1;
	unsigned char *ptr2;

	ptr1 = dst;
	ptr2 = (unsigned char *)src;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (n--)
		*ptr1++ = *ptr2++;
	return (dst);
}
