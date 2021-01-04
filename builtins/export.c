/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:57:13 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/04 16:06:32 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int     export(t_arguments *args, t_env_vars **envs)
{
    char        *name;
    char        *value;
    int         ret;
    t_arguments *tmp;
    t_env_vars  *var_node;

    if (!args)
        return (1);
    tmp = args;
    ret = 0;
   while (tmp)
   {
        name = get_env_name(tmp->arg);
        value = get_env_value(tmp->arg);
        if(name)
        {
            if (is_identifier(name))
                change_env_var(envs, name, value);
            else
            {
                ret = 1;
                printf("not a valid identifier '%s'\n", name);
            }
        }
        tmp = tmp->next;
    }
    return(ret);
}