/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 09:14:27 by abbouzid          #+#    #+#             */
/*   Updated: 2019/10/17 17:48:53 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
