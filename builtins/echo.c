/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 09:45:21 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/15 09:47:05 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int     echo(char   **args)
{
    bool    new_line;
    int     i;

    new_line = ft_strcmp(args[1], "-n");
    i = (!new_line)? 2: 1;
    while (args[i])
    {
        ft_putstr_fd(args[i], 1);
        if (args[i + 1])
            ft_putstr_fd(" ", 1);
        i++;
    }
    if (new_line != 0)
        ft_putstr_fd("\n", 1);
    return (1);
}
