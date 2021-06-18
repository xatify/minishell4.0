/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 01:28:50 by keddib            #+#    #+#             */
/*   Updated: 2021/06/18 13:26:43 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_strrev(char *str)
{
	int		i;
	int		l;
	char	swap;

	i = 0;
	l = 0;
	while (str[i] != '\0')
		i++;
	i = i - 1;
	while (l < i)
	{
		swap = str[l];
		str[l] = str[i];
		str[i] = swap;
		l++;
		i--;
	}
	return (str);
}

static int	ft_neg(int i)
{
	int	negative;

	negative = 0;
	if (i < 0)
		negative = 1;
	return (negative);
}

static char	*ft_str(char *s, int n, int neg)
{
	int		i;
	int		rep;

	i = 0;
	if (n == 0)
		s[i++] = '0';
	while (n != 0)
	{
		rep = n % 10;
		s[i] = rep + '0';
		n = n / 10;
		i++;
	}
	if (neg)
		s[i++] = '-';
	s[i] = '\0';
	return (s);
}

static int	ft_len(int n)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	int		neg;
	char	*s;

	neg = ft_neg(n);
	if (n == -2147483648)
	{
		s = ft_calloc(12, 1);
		ft_memcpy(s, "-2147483648", 11);
		return (s);
	}
	if (neg)
		n = -n;
	i = ft_len(n);
	if (neg || n == 0)
		s = malloc((i + 2) * sizeof(char));
	else
		s = malloc((i + 1) * sizeof(char));
	if (!s)
		return (NULL);
	ft_str(s, n, neg);
	ft_strrev(s);
	return (s);
}
