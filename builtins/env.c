/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 11:14:24 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/20 10:25:26 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int     env(char *arg0, t_env_vars *env_vars)
{
    if (arg0)
    {
        ft_putstr_fd("env arg not supported yet", 2);
        return (0);
    }
    if (env_vars)
    {
        ft_putstr_fd(env_vars->name, 1);
        ft_putstr_fd("=", 1);
        ft_putstr_fd(env_vars->value, 1);
        ft_putchar_fd('\n', 1);
        env(NULL, env_vars->next);
    }
    return (1);
}
