/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 14:54:05 by abbouzid          #+#    #+#             */
/*   Updated: 2019/10/14 14:34:15 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	if (dst == NULL && src == NULL)
		return (NULL);
	ptr2 = (unsigned char *)src;
	ptr1 = dst;
	if (dst > src && dst < src + len)
	{
		ptr1 = ptr1 + len - 1;
		ptr2 = ptr2 + len - 1;
		while (len--)
			*ptr1-- = *ptr2--;
	}
	else
		ft_memcpy(ptr1, ptr2, len);
	return (dst);
}
