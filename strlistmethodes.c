/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlistmethodes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 10:04:18 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/25 14:27:56 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

t_strlist *new_strlist(char   *str)
{
    t_strlist *args;

    if (!(args = (t_strlist *)malloc(sizeof(t_strlist))))
        return (NULL);
    if (!(args->str = ft_strdup(str)))
    {
        free(args);
        return (NULL);
    }
    args->next = NULL;
    return (args);
}

t_strlist *last_strlist(t_strlist *strlist)
{
    if (!(strlist))
        return (strlist);
    if (!(strlist->next))
        return (strlist);
    return (last_strlist(strlist->next));
}

int     add_strlist(t_strlist **strlist, char *str)
{
    t_strlist *tmp;

    if (!(tmp = new_strlist(str)))
        return (0);
    if (!(*strlist))
        (*strlist) = tmp;
    else
        (last_strlist((*strlist)))->next = tmp;
    return (1);
}

void                free_strlist(t_strlist *strlist)
{
    if (!strlist)
        return;
    free_strlist(strlist->next);
    free(strlist->str);
    free(strlist);
    
}

void        show_strlist(t_strlist *strlist)
{
    if (strlist)
    {
        //if (strlist->str)
            ft_putstr_fd(strlist->str, 1);
            ft_putchar_fd('\t', 1);
        show_strlist(strlist->next);
    }
}
