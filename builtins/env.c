/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 11:14:24 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/04 11:32:13 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int     env(t_env_vars *env_vars)
{
    if (env_vars)
    {
        printf("%s=%s\n", env_vars->name, env_vars->value);
        env(env_vars->next);
    }
    return (1);
}