/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 09:29:16 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/15 12:29:42 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* change corrent directory to path if path is not null otherwise to $HOME */

int     cd(char *path, t_env_vars **vars)
{
    char    *dir;
    int     ret;
    char    *pwd;

    dir = (path) ? path: search_var(vars, "HOME")->value;
    pwd = getcwd(NULL, 0);
    ret = chdir(dir);
    if (!ret && pwd)
    {
       change_env_var(vars, "OLDPWD", pwd);
       free(pwd);
        pwd = getcwd(NULL, 0);
       change_env_var(vars, "PWD", pwd); 
    }
    else
        ft_putstr_fd("no such file or directory\n", 2);  
    return (!ret);
}