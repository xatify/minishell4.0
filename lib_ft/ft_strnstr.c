/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:09:29 by abbouzid          #+#    #+#             */
/*   Updated: 2019/10/14 17:00:52 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	inc1;
	size_t	inc2;
	char	*s;

	inc1 = 0;
	inc2 = 0;
	if (*to_find == '\0')
		return ((char *)str);
	while (str[inc1] != '\0' && inc1 < len)
	{
		inc2 = 0;
		while (inc2 < ft_strlen(to_find) && (inc1 + inc2) < len)
		{
			if (to_find[inc2] != str[inc1 + inc2])
				break ;
			if (inc2 == (ft_strlen(to_find) - 1))
			{
				s = (char *)str;
				return (&s[inc1]);
			}
			inc2++;
		}
		inc1++;
	}
	return (0);
}
