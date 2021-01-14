/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 11:14:24 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/14 09:31:46 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int     env(t_env_vars *env_vars)
{
    if (env_vars)
    {
        ft_putstr_fd(env_vars->name, 1);
        ft_putstr_fd(env_vars->value, 1);
        ft_putchar_fd('\n', 1);
        env(env_vars->next);
    }
    return (1);
}
