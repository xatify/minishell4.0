/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 18:25:11 by abbouzid          #+#    #+#             */
/*   Updated: 2019/10/21 22:24:09 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	char	*ptrb;

	if (s == NULL || len == 0)
		return (0);
	if (ft_strlen(s) < start)
	{
		ptr = ft_calloc(1, 1);
		return (ptr);
	}
	ptr = (char *)ft_calloc(len + 1, 1);
	if (!ptr)
		return (0);
	s = s + start;
	ptrb = ptr;
	while (len-- && *s)
		*ptr++ = *s++;
	return (ptrb);
}
