/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 16:30:47 by abbouzid          #+#    #+#             */
/*   Updated: 2021/06/18 18:02:05 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	putchar_2(int c)
{
	return (write(STDERR, &c, 1));
}

int	is_print(char c)
{
	if ((c >= 32 && c <= 126) || c == 9)
		return (TRUE);
	return (FALSE);
}
