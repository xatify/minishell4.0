/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 09:29:16 by abbouzid          #+#    #+#             */
/*   Updated: 2021/02/02 10:39:44 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* change corrent directory to path if path is not null otherwise to $HOME */

int    hundle_removed_path(char *path, t_list **vars, t_data *data)
{
    t_env_var   *var_env;
    char        *tmp;
    int         i;
    
    i = 0;
    while (path[i])
        i++;
    if ((var_env = search_var(&(data->env_vars), "PWD")))
    {
        tmp = (path[--i] != '/') ? ft_strjoin("/", path) : path;
        change_env_var(vars, "OLDPWD", var_env->value);
        change_env_var(vars, "PWD", ft_strjoin(var_env->value, tmp));
    }
    ft_putstr_fd("cd: error retrieving current directory\n", 2);
    return (0);
}

int     cd(char *path, t_data *data)
{
    char        *dir;
    int         ret;
    char        *pwd;
    t_env_var   *var_env;
    
    if ((var_env = search_var(&(data->env_vars), "HOME")))
        dir = var_env->value;
    dir = (path) ? path: dir;
    pwd = getcwd(NULL, 0);
    ret = chdir(dir);
    dir = NULL;
    dir = getcwd(NULL, 0);
    if (!ret && (pwd || dir))
    {
        if (pwd)
            change_env_var(&(data->env_vars), "OLDPWD", pwd);
        else
        {
             if ((var_env = search_var(&(data->env_vars), "PWD")))
                change_env_var(&(data->env_vars), "OLDPWD", var_env->value);
        }
        free(pwd);
        pwd = getcwd(NULL, 0);
        change_env_var(&(data->env_vars), "PWD", pwd);
    }
    else if (!pwd && !ret)
    {
        hundle_removed_path(path, &(data->env_vars), data);
        return (1);
    }
    else
    {
        ft_putstr_fd("no such file or directory\n", 2);
        return (1);
    }
    return (ret);
}
