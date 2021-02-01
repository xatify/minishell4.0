/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 11:01:58 by abbouzid          #+#    #+#             */
/*   Updated: 2021/02/01 17:48:18 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int     pwd(t_data *data)
{
    char        *cwd;
    t_env_var   *var_env;
    
    cwd = NULL;
    cwd = getcwd(cwd, 0);
    if (cwd)
    {
        ft_putstr_fd(cwd, 1);
        ft_putchar_fd('\n', 1);
        free(cwd);
        return (1);
    }
    else
    {
        if ((var_env = search_var(&(data->env_vars), "PWD")))
        {
            ft_putstr_fd(var_env->value, 1);
            ft_putchar_fd('\n', 1);
        }
    }
    return (0);
}