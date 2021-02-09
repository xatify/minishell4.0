/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 11:14:24 by abbouzid          #+#    #+#             */
/*   Updated: 2021/02/09 15:46:51 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		env(char *arg0, t_list *env_vars)
{
	if (arg0)
	{
		ft_putstr_fd(ARG_NOT_SUP, STDERR);
		return (0);
	}
	if (env_vars)
	{
		ft_putstr_fd(((t_env_var *)(env_vars->content))->name, STDOUT);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(((t_env_var *)(env_vars->content))->value, STDOUT);
		ft_putchar_fd('\n', STDOUT);
		env(NULL, env_vars->next);
	}
	return (1);
}
