/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 09:12:22 by abbouzid          #+#    #+#             */
/*   Updated: 2021/07/02 19:50:05 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_len(char **strings)
{
	int	len;

	len = 0;
	while (strings[len])
		len++;
	return (len);
}

void	sort(char **strings)
{
	int		i;
	int		j;
	char	*swap;
	int		len;

	len = count_len(strings);
	i = 1;
	while (i < len)
	{
		j = i;
		while (j > 0 && ft_strcmp(strings[j - 1], strings[j]) > 0)
		{
			swap = strings[j - 1];
			strings[j - 1] = strings[j];
			strings[j] = swap;
			j--;
		}
		i++;
	}
}

void	LCG(char **str, int len)
{
	int				i;
	static int		seed;
	static int		m;
	char			s[10];

	m = (1 << 31);
	i = 0;
	while (i < len)
	{
		seed = (1103515245 * seed + 12345) % m;
		if (seed < 0)
			s[i] = (char )((-seed % 24) + 'a');
		else
			s[i] = (char)((seed % 24) + 'a');
		i++;
	}
	s[len] = '\0';
	*str = ft_strjoin("/tmp/", s);
}

int	lkhra(t_list *tokens, t_token *token)
{
	int		next_id;

	if (token->id == SEMICOLON || token->id == PIPE)
	{
		if (!(tokens->next))
			return (token->id == SEMICOLON);
		next_id = token_id(((t_token *)((tokens->next)->content))->tkn);
		if (next_id <= 3)
			return (2);
		else if (next_id == SEMICOLON || next_id == PIPE)
			return (0);
	}
	if (!(tokens->next))
		return (0);
	if (token_id(((t_token *)((tokens->next)->content))->tkn) != WORD)
		return (0);
	return (-1);
}
