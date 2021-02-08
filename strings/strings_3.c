/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 12:05:50 by keddib            #+#    #+#             */
/*   Updated: 2021/02/08 18:32:11 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

BOOL	is_num(char c)
{
	if (c >= 0x30 && c <= 0x39)
		return (TRUE);
	return (FALSE);
}

int		ft_atoi(const char *str, int *exit)
{
	long	res;
	int		sign;
	long	max;

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

char	*ft_strchr(const char *str, int c)
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

void	free_tmp(char **tmp)
{
	free(*tmp);
	*tmp = NULL;
}
