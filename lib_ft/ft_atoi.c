/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:29:45 by abbouzid          #+#    #+#             */
/*   Updated: 2019/10/21 17:35:20 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
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
	while (ft_isdigit(*str))
	{
		if (res <= (max - (*str - '0')) / 10)
			res = res * 10 + (*str++ - '0');
		else
		{
			res = (sign == -1) ? 0 : -1;
			break ;
		}
	}
	return (res * sign);
}
