/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:55:39 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/04 16:20:13 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int     unset(t_arguments *arguments, t_env_vars **envs)
{
    int         ret;
    t_arguments *tmp;
    
    ret = 0;
    tmp = arguments;    
    while(tmp)
    {
        if (is_identifier(tmp->arg))
            del_env_var(envs, tmp->arg);
        else
            ret = 1;
        tmp = tmp->arg;
    }
    return (ret);
}