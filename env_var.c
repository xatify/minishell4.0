/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 11:28:41 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/31 08:50:05 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void    free_env_var(t_env_var *var)
{
    free(var->name);
    free(var->value);
    free(var);
}

t_list      *build_env_vars(char **envp)
{
    t_list      **list_head;
    t_list      *new;
    t_env_var   *var;
    char        *tmp;
    int         i;

    i = 0;
    *list_head = NULL;
    while (envp[i])
    {
        if (!(var = (t_env_var *)malloc(sizeof(t_env_var))))
        {
            ft_lstclear((*list_head), free_env_var);
            return (NULL);
        }
        var->name = get_env_value(envp[i]);
        if (ft_strcmp(var->name, "SHELL") == 0)
            var->value = ft_strdup("minishell");
        else if (ft_strcmp(var->name, "SHLVL") == 0)
        {
            tmp = get_env_value(envp[i]);
            var->value = ft_itoa(ft_atoi(tmp) + 1);
            free(tmp);
        }
        else
            var->value = get_env_value(envp[i]);
        
        if (!(new = ft_lstnew(var)))
        {
            free_env_var(var);
            ft_lstclear((*list_head), free_env_var);
        }
        ft_lstadd_back(list_head, new);
        i++;
    }
    return ((*list_head));
}

char    *get_env_name(char *name_value)
{
    char    *name;
    int     i;

    i = 0;
    while (name_value[i] && name_value[i] != '=')
        i++;
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

    value = ft_strdup(&name_value[i + 1]);
    return (value);
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

void    fill_envp(char **envp_i, t_env_vars *vars)
{
    int     name_len;

    name_len = ft_strlen(vars->name);
    ft_strcpy(*envp_i, vars->name);
    (*envp_i)[name_len] = '=';
    ft_strcpy((*envp_i) + name_len + 1, vars->value);
}


char    **built_envp(t_env_vars *vars)
{
    char    **envp;
    int     vars_num;
    int     i;

    vars_num = vars->num + 1;
    if (!(envp = (char **)malloc(sizeof(char *) * vars_num)))
        return (NULL);
    ft_memset(envp, 0, vars_num * sizeof(char *));
    i = 0;
    while (vars)
    {
        if (!(envp[i] = (char *)malloc(ft_strlen(vars->name) + ft_strlen(vars->value) + 2)))
        {
            free_argv(envp);
            return (NULL);
        }
        fill_envp(&(envp[i]), vars);
        vars = vars->next;
        i++;
    }
    envp[i] = NULL;
    return(envp);
}
