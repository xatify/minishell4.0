/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:55:39 by abbouzid          #+#    #+#             */
/*   Updated: 2021/02/01 15:14:26 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int     unset(char **args, t_list **envs)
{
    int     index;
    int     ret;

    ret = 0;
    index = 1;
    while (args[index])
    {
        if (is_identifier(args[index]))
            del_env_var(envs, args[index]);
        else
        {
            ft_putstr_fd("unset: ", 2);
            ft_putstr_fd(args[index], 2);
            ft_putstr_fd(" not a valid identifier\n", 2);
            ret = 1;
        
        }
        index++;
    }
    return (ret);
}

