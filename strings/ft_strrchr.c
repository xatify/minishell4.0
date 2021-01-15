/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 09:14:27 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/15 10:27:54 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
