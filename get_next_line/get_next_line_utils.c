/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 13:34:29 by abbouzid          #+#    #+#             */
/*   Updated: 2021/06/18 11:47:28 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;

	if (s == NULL)
		return (0);
	if (ft_strlen_(s) < start)
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

char	*ft_strdup_(const char *s1)
{
	char	*ptr;
	int		i;

	i = 0;
	while (s1[i])
		i++;
	ptr = malloc(i + 1);
	if (!ptr)
		return (0);
	i = -1;
	while (s1[++i] != '\0')
		ptr[i] = s1[i];
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strjoin_(char const *s1, char const *s2, int d)
{
	int		i;
	int		j;
	int		k;
	char	*str;

	j = 0;
	i = 0;
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	str = malloc(i + j + 1);
	if (!str)
		return (0);
	k = -1;
	while (++k < i)
		str[k] = s1[k];
	k = -1;
	while (++k < j)
		str[i + k] = s2[k];
	str[i + j] = '\0';
	free((void *)s1);
	if (d)
		free((void *)s2);
	return (str);
}

size_t	ft_strlen_(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (0);
	ft_bzero(ptr, count * size);
	return (ptr);
}
