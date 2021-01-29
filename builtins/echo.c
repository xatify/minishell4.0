/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 09:45:21 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/29 08:57:12 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int     echo(char   **args)
{
    bool    new_line;
    int     i;
    int     argsnum;

    argsnum = args_num(args);
    if (argsnum >= 2)
        new_line = ft_strcmp(args[1], "-n");
    else
        new_line = 1;
    i = 1;
    while (ft_strcmp(args[i], "-n") == 0)
        i++;
    while (args[i])
    {
        if (args[i][0])
        {
            ft_putstr_fd(args[i], 1);
            if (args[i + 1] && args[i + 1][0])
                ft_putstr_fd(" ", 1);
        }
        i++;
    }
    if (new_line != 0)
        ft_putstr_fd("\n", 1);
    return (0);
}
