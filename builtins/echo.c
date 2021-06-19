/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 09:45:21 by abbouzid          #+#    #+#             */
/*   Updated: 2021/06/19 09:55:14 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	echo_(char **args)
{
	BOOL	new_line;
	int		i;
	int		j;
	int		brk;

	new_line = 1;
	i = 1;
	brk = 0;
	while (args[i])
	{
		j = 0;
		if (args[i][j] == '-')
		{
			j++;
			while (args[i][j])
			{
				if (args[i][j] == 'n')
					j++;
				else
				{
					new_line = 1;
					brk = 1;
					break ;
				}
			}
			if (brk == 1)
				break ;
			new_line = 0;
		}
		else
			break;
		i++;
	}
	while (args[i])
	{
		if (args[i][0])
		{
			ft_putstr_fd(args[i], STDOUT);
			if (args[i + 1] && args[i + 1][0])
				ft_putstr_fd(" ", STDOUT);
		}
		i++;
	}
	if (new_line == 1)
		ft_putstr_fd("\n", STDOUT);
	return (0);
}
