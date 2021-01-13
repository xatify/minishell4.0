/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 19:34:24 by abbouzid          #+#    #+#             */
/*   Updated: 2019/10/20 16:36:33 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		is_inset(char const *set, char c)
{
	int i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	size_t	i;
	size_t	j;

	if (s1 == NULL)
		return (NULL);
	i = 0;
	while (is_inset(set, s1[i]))
		i++;
	if (i == ft_strlen(s1))
	{
		trim = malloc(1);
		if (!trim)
			return (0);
		trim[0] = '\0';
		return (trim);
	}
	j = ft_strlen(s1) - 1;
	while (is_inset(set, s1[j]))
		j--;
	trim = malloc(j - i + 2);
	if (!trim)
		return (0);
	ft_strlcpy(trim, s1 + i, j - i + 2);
	return (trim);
}
