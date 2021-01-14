/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 11:28:41 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/14 09:33:03 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_env_vars  *create_env_var(char *name, char *value)
{
    t_env_vars  *env_var;

    if (!(env_var = (t_env_vars *)malloc(sizeof(t_env_vars))))
        return (NULL);
    env_var->name = (char *)malloc(ft_strlen(name) + 1);
    if (env_var->name == NULL)
    {
        free(env_var);
        return (NULL);
    }
    env_var->value = (char *)malloc(ft_strlen(value) + 1);
    if (env_var->value == NULL)
    {
        free(env_var->name);
        free(env_var);
        return (NULL);
    }
    ft_strcpy(env_var->name, name);
    ft_strcpy(env_var->value, value);
    env_var->next = NULL;
    return (env_var);
}

char    *get_env_name(char *name_value)
{
    char    *name;
    int     i;

    i = 0;
    while (name_value[i] && name_value[i] != '=')
        i++;
    if (!name_value[i])
        return (NULL);
    if (!(name = (char *)malloc(i + 1)))
        return (NULL);
    ft_strlcpy(name, name_value, i);
    name[i] = '\0';
    return (name);
}

char    *get_env_value(char *name_value)
{
    char    *value;
    int     i;

    i = 0;
    while (name_value[i] && name_value[i] != '=')
        i++;
    if (name_value[i] == '\0')
        i--;
    if (!(value = (char *)malloc(ft_strlen(&name_value[i + 1]) + 1)))
        return (NULL);
    ft_strcpy(value, &name_value[i + 1]);
    return (value);
}

t_env_vars  *last_env_var(t_env_vars *env_vars)
{
    t_env_vars  *tmp;

    if (!env_vars)
        return (env_vars);
    tmp = env_vars;
    if (!tmp->next)
        return (tmp);
    return (last_env_var(tmp->next));
}

void       add_back_env(t_env_vars **vars, t_env_vars *new_var)
{
    if (!(*vars))
        (*vars) = new_var;
    else
        last_env_var((*vars))->next = new_var;
}

t_env_vars  *build_env_vars(char *envp[])
{
    t_env_vars      *vars;
    char            *name;
    char            *value;
    int             i;

    vars = NULL;
    i = 0;
    while (envp[i])
    {
        name = get_env_name(envp[i]);
        value = get_env_value(envp[i]);
        add_back_env(&vars, create_env_var(name, value));
        free(name);
        free(value);
        i++;
    }
    return (vars);
}

t_env_vars      *search_var(t_env_vars **env_vars, char *var_name)
{
    t_env_vars *tmp;

    tmp = (*env_vars);
    while (tmp)
    {
        if (ft_strcmp(tmp->name, var_name) == 0)
            return (tmp);
        tmp = tmp->next;
    }
    return (tmp);
}

int             change_env_var(t_env_vars **vars, char *var_name, char *new_value)
{
    t_env_vars  *var;

    var = search_var(vars, var_name);
    if (var)
    {
        free(var->value);
        if (!(var->value = (char *)malloc(ft_strlen(new_value) + 1)))
            return (0);
        ft_strcpy(var->value, new_value);
    }
    else
    {
        var = create_env_var(var_name, new_value);
        if (var)
            add_back_env(vars, var);
        else
            return (0);
    }
    return (1);
}

void    del_env_var(t_env_vars **envs, char *name)
{
    t_env_vars *tmp;
    t_env_vars *prev;

    tmp = (*envs);
    if (!ft_strcmp((*envs)->name, name))
    {
        tmp = (*envs)->next;
        free_env_var((*envs));
        (*envs) = tmp;
        return;
    }
    prev = (*envs);
    tmp = (*envs)->next;
    while (tmp)
    {
        if (!ft_strcmp(tmp->name, name))
        {
            prev->next = tmp->next;
            free_env_var(tmp);
            return;
        }
        prev = tmp;
        tmp = tmp->next;
    }
}

void    free_env_var(t_env_vars *var)
{
    free(var->name);
    free(var->value);
    free(var);
}

void    show_env_vars(t_env_vars *vars)
{
    if (vars)
    {
        ft_putstr_fd(vars->name, 1);
        ft_putstr_fd(vars->value, 1);
        ft_putchar_fd('\n', 1);
        show_env_vars(vars->next);
    }
}
