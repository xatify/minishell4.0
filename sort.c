/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 09:12:22 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/16 09:32:22 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int     _len(char **strings)
{
    int len;

    len = 0;
    while (strings[len])
        len++;
    return (len);
}

void    sort(char **strings)
{
    int     i;
    int     j;
    char    *swap;
    int     len;

    len = _len(strings);
    i = 1;
    while (i < len)
    {
        j = i;
        while (j > 0 && ft_strcmp(strings[j-1], strings[j]) > 0)
        {
            swap = strings[j-1];
            strings[j - 1] = strings[j];
            strings[j] = swap;
            j--;
        }
        i++;
    }   
}    