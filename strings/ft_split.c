/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 11:03:46 by abbouzid          #+#    #+#             */
/*   Updated: 2021/04/04 16:48:27 by abbouzid         ###   ########.fr       */
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

static void		alloc_mem(char **tab_, size_t x, size_t l)
{
	tab_[x] = (char *)malloc((l + 1) * sizeof(char));
	if (!tab_[x])
	{
		while ((int)x >= 0)
			free(tab_[x--]);
		free(tab_);
		tab_ = NULL;
	}
}

static void		fill_tab_(char **tab_, const char *str, size_t count, char c)
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
		alloc_mem(tab_, x, l);
		if (!tab_)
			break ;
		y = -1;
		while (++y < l)
			tab_[x][y] = str[y];
		tab_[x][y] = '\0';
		str = str + l;
	}
	if (tab_)
		tab_[x] = 0;
}

char			**ft_split(char const *str, char c)
{
	char	**tab_;
	size_t	count;

	if (str == NULL)
		return (NULL);
	count = count_words(str, c);
	tab_ = (char **)malloc((count + 1) * sizeof(char *));
	if (!tab_)
		return (NULL);
	fill_tab_(tab_, str, count, c);
	return (tab_);
}
