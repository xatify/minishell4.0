/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 09:04:09 by keddib            #+#    #+#             */
/*   Updated: 2021/06/23 17:15:14 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_alpha(char c)
{
	if ((c >= 0x41 && c <= 0x5a) || (c >= 0x61 && c <= 0x7a))
		return (TRUE);
	return (FALSE);
}

int	is_underscore(char c)
{
	if (c == '_')
		return (TRUE);
	return (FALSE);
}

int	is_identifier(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (i == 0)
		{
			if (!(is_alpha(str[i]) || is_underscore(str[i])))
				break ;
		}
		else
		{
			if (!(is_alpha(str[i]) || is_underscore(str[i]) || is_num(str[i])))
				break ;
		}
	}
	if (str[i] == '\0')
		return (TRUE);
	return (FALSE);
}

int	is_white_character(char c)
{
	if (c == ' ' || c == '\t')
		return (TRUE);
	return (FALSE);
}
