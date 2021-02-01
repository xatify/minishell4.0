/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 09:04:09 by keddib            #+#    #+#             */
/*   Updated: 2021/02/01 17:43:45 by abbouzid         ###   ########.fr       */
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

char    *ft_strchr(const char *str, int c)
{
        char *ptr;

        ptr = (char *)str;
        while (*ptr != '\0')
        {
                if (*ptr == (char)c)
                        return (ptr);
                else
                        ptr++;
        }
        if (c == '\0')
                return (ptr);
        return (0);
}

int     ft_atoi(const char *str, int *exit)
{
        long    res;
        int             sign;
        long    max;

        max = 9223372036854775807;
        res = 0;
        sign = 1;
        while (*str == ' ' || (*str >= 9 && *str <= 13))
                str++;
        if (*str == '-' || *str == '+')
                sign = (*str++ == '-') ? -1 : 1;
        while (is_num(*str))
        {
                if (res <= (max - (*str - '0')) / 10)
                        res = res * 10 + (*str++ - '0');
                else
                {
                        if (exit)
                                *exit = 1;
                        res = (sign == -1) ? 0 : -1;
                        break ;
                }
        }
        return (res * sign);
}