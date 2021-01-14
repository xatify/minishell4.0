/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 11:03:46 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/14 09:02:51 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static size_t	count_words(char const *str, char c)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else if (str[i] != c && str[i])
		{
			j++;
			while (str[i] != c && str[i])
				i++;
		}
	}
	return (j);
}

static void		alloc_mem(char **tab, size_t x, size_t l)
{
	tab[x] = (char *)malloc((l + 1) * sizeof(char));
	if (!tab[x])
	{
		while ((int)x >= 0)
			free(tab[x--]);
		free(tab);
		tab = NULL;
	}
}

static void		fill_tab(char **tab, const char *str, size_t count, char c)
{
	size_t	x;
	size_t	y;
	size_t	l;

	x = -1;
	while (++x < count)
	{
		l = 0;
		while (*str == c)
			str++;
		while (str[l] != c && str[l])
			l++;
		alloc_mem(tab, x, l);
		if (!tab)
			break ;
		y = -1;
		while (++y < l)
			tab[x][y] = str[y];
		tab[x][y] = '\0';
		str = str + l;
	}
	if (tab)
		tab[x] = 0;
}

char			**ft_split(char const *str, char c)
{
	char	**tab;
	size_t	count;

	if (str == NULL)
		return (NULL);
	count = count_words(str, c);
	tab = (char **)malloc((count + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	fill_tab(tab, str, count, c);
	return (tab);
}
