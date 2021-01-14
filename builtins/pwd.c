/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 11:01:58 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/14 09:26:22 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int     pwd(void)
{
    char    *cwd;

    cwd = NULL;
    cwd = getcwd(cwd, 0);
    if (cwd)
    {
        ft_putstr_fd(cwd, 1);
        free(cwd);
        return (1);
    }
    return (0);
}
