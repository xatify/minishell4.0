/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:55:39 by abbouzid          #+#    #+#             */
/*   Updated: 2021/06/18 11:08:41 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	unset(char **args, t_list **envs)
{
	int		index;
	int		ret;

	ret = 0;
	index = 1;
	while (args[index])
	{
		if (is_identifier(args[index]))
			del_env_var(envs, args[index]);
		else
		{
			ft_putstr_fd("unset: ", STDERR);
			ft_putstr_fd(args[index], STDERR);
			ft_putstr_fd(NOT_IDEN, STDERR);
			ft_putchar_fd('\n', STDERR);
			ret = 1;
		}
		index++;
	}
	return (ret);
}
