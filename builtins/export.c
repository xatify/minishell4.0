/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:57:13 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/14 09:25:26 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int     export(char   **args, t_env_vars **envs)
{
    char    *name;
    char    *value;
    int     index;
    int     return_value;

    return_value = 1;
    index = 1;
    while (args[index])
    {
        name = get_env_name(args[index]);
        value = get_env_value(args[index]);
        if (name)
        {
            if (is_identifier(name))
                change_env_var(envs, name, value);
            else
            {
                return_value = 0;
                // redirect error to standard error
                ft_putstr_fd("not a valid identifier ", 1);
                ft_putstr_fd(name, 1);
                ft_putchar_fd('\n', 1);
            }
            free(name);
        }
        if (value)
            free(value);
        index++;
    }
    return (return_value);
}
