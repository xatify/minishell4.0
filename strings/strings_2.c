/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 09:04:09 by keddib            #+#    #+#             */
/*   Updated: 2021/01/14 09:05:39 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_alpha(char c)
{
	if ((c >= 0x41 && c <= 0x5a) || (c >= 0x61 && c <= 0x7a))
		return (TRUE);
	return (FALSE);
}

bool	is_num(char c)
{
	if (c >= 0x30 && c <= 0x39)
		return (TRUE);
	return (FALSE);
}

bool is_underscore(char c)
{
	return ((c == '_')? TRUE: FALSE);
}

bool    is_identifier(char *str)
{
    int i;

    i = -1;
    while (str[++i])
    {
        if (i == 0)
        {
            if (!(is_alpha(str[i]) || is_underscore(str[i])))
                break;
        }
        else
        {
            if (!(is_alpha(str[i]) || is_underscore(str[i]) || is_num(str[i])))
                break;
        }
    }
    return ((str[i] == '\0')? TRUE: FALSE);
}

bool	is_white_character(char c)
{
	return ((c == ' ' || c == '\t') ? TRUE: FALSE);
}
