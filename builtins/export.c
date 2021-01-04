/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 11:30:54 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/04 12:04:44 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool    is_identifier(char *str)
{
    int i;

    i = -1;
    while (str[++i])
    {
        if (i == 0)
        {
            if (!(is_alpha(str[i]) || is_undercore(str[i])))
                break;
        }
        else
        {
            if (!(is_alpha(str[i]) || is_underscore(str[i]) || is_num(str[i])))
                break;
        }
    }
    return ((str[i] == '\0')? TRUE: FALSE);
}

int     export(t_arguments *args)
{
    char    *var;

    if (!args)
        return (1);
    var = args->arg;
    
}