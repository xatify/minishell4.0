/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 15:55:00 by abbouzid          #+#    #+#             */
/*   Updated: 2019/10/13 19:39:09 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	char	*ptrb;
	int		i;

	i = 0;
	while (s1[i])
		i++;
	ptrb = malloc(i + 1);
	if (!ptrb)
		return (0);
	ptr = ptrb;
	while (*s1)
		*ptr++ = *s1++;
	*ptr = '\0';
	return (ptrb);
}
