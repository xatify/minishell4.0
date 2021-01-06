/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 09:45:21 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/06 09:56:14 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int     echo(t_arguments *args)
{
    int new_line;

    new_line = ft_strcmp(args->arg, "\n");
    if (new_line)
        args = args->next;
    while(args)
    {
        printf("%s");
        if(args->next)
            printf(" ");
        args = args->next;
    }
    if (!new_line)
        printf("\n");
    return (1);
}