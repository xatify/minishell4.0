/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 09:45:21 by abbouzid          #+#    #+#             */
/*   Updated: 2021/06/19 14:25:56 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_param(char **args, int *i, int *new_line)
{
	int		j;

	while (args[++(*i)])
	{
		j = 0;
		if (args[*i][j++] == '-')
		{
			while (args[*i][j])
			{
				if (args[*i][j] == 'n')
					j++;
				else
				{
					*new_line = 1;
					j = -1;
					break ;
				}
			}
			if (j == -1)
				break ;
			*new_line = 0;
		}
		else
			break ;
	}
}

int	echo_(char **args)
{
	BOOL	new_line;
	int		i;

	new_line = 1;
	i = 0;
	check_param(args, &i, &new_line);
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT);
		if (args[i + 1])
			ft_putstr_fd(" ", STDOUT);
		i++;
	}
	if (new_line == 1)
		ft_putstr_fd("\n", STDOUT);
	return (0);
}
