/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 16:30:47 by abbouzid          #+#    #+#             */
/*   Updated: 2021/06/27 15:55:28 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (0);
	ft_bzero(ptr, count * size);
	return (ptr);
}

char	*ft_substr(char *s, int start, size_t len)
{
	char	*ptr;
	size_t	i;

	if (s == NULL)
		return (0);
	if (ft_strlen(s) < start)
	{
		ptr = ft_calloc(1, 1);
		return (ptr);
	}
	ptr = (char *)ft_calloc(len + 1, 1);
	if (!ptr)
		return (0);
	i = -1;
	while (++i < len && *s)
		ptr[i] = (s + start)[i];
	return (ptr);
}

void	ft_bzero(void *str, size_t n)
{
	int	i;

	i = -1;
	while (++i < (int)n)
		((unsigned char *)str)[i] = 0;
}
