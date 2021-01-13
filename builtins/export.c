/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:57:13 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/13 10:07:44 by abbouzid         ###   ########.fr       */
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
                printf("not a valid identifier '%s'\n", name);
            }
            free(name);
        }
        if (value)
            free(value);
        index++;
    }
    return (return_value);    
}