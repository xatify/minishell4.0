/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 11:01:58 by abbouzid          #+#    #+#             */
/*   Updated: 2021/02/09 15:40:29 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <sys/stat.h>

int		pwd(t_data *data)
{
	char		*cwd;
	t_env_var	*var_env;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (cwd)
	{
		ft_putstr_fd(cwd, STDOUT);
		ft_putchar_fd('\n', STDOUT);
		free(cwd);
		return (1);
	}
	else
	{
		if ((var_env = search_var(&(data->env_vars), "PWD")))
		{
			ft_putstr_fd(var_env->value, STDOUT);
			ft_putchar_fd('\n', STDOUT);
		}
	}
	return (0);
}
