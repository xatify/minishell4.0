/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 11:14:24 by abbouzid          #+#    #+#             */
/*   Updated: 2021/02/05 14:30:05 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		env(char *arg0, t_list *env_vars)
{
	if (arg0)
	{
		ft_putstr_fd("env arg not supported yet", 2);
		return (0);
	}
	if (env_vars)
	{
		ft_putstr_fd(((t_env_var *)(env_vars->content))->name, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(((t_env_var *)(env_vars->content))->value, 1);
		ft_putchar_fd('\n', 1);
		env(NULL, env_vars->next);
	}
	return (1);
}
