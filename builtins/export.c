/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:57:13 by abbouzid          #+#    #+#             */
/*   Updated: 2021/02/02 15:07:50 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void      show_vars(t_data *data)
{
    int     i;
    char    **vars;

    vars = get_all_vars(data->env_vars, data->unset_vars);
    sort(vars);
    i = 0;
    while (vars[i])
    {
        ft_putstr_fd("declare -x ", 1);
        ft_putstr_fd(vars[i], 1);
        ft_putstr_fd("\n", 1);
        i++;
    }
    free_argv(vars);
}

bool    is_unset_var(t_list **unset_vars, char *name)
{
    t_list *tmp;

    tmp = *(unset_vars);
    while (tmp)
    {
        if (ft_strcmp(tmp->content, name) == 0)
            return (TRUE);
        tmp = tmp->next;
    }
    return (FALSE);
}

int             append_env_var(t_list **vars, char *var_name, char *new_value)
{
    t_env_var  *var;
    char    *tmp;
    
    var = search_var(vars, var_name);
    if (var)
    {
        if (!(tmp = ft_strjoin(var->value, new_value)))
            return (0);
        free(var->value);
        var->value = tmp;
    }
    else
    {
        var = create_env_var(var_name, new_value);
        if (var)
            ft_lstadd_back(vars, ft_lstnew(var));
        else
            return (0);
    }
    return (1);
}

void        remove_unset_var(t_list **unset_vars, char *name)
{
    t_list      *tmp;
    t_list      *last;
    
    last = NULL;
    tmp = *(unset_vars);
    while (tmp)
    {
        if (ft_strcmp(tmp->content, name) == 0)
        {
            if (tmp->next)
            {
                if (last == NULL)
                    (*unset_vars) = tmp->next;
                else
                    last->next = tmp->next;
            }
            else if (last == NULL)
                (*unset_vars) = NULL;
            else
                last->next = NULL;
            free(tmp->content);
            free(tmp);
            return;
        }
        last = tmp;
        tmp = tmp->next;
    }
}

int     export(char   **args, t_data *data)
{
    char    *name;
    char    *value;
    int     index;
    int     end;
    int     return_value;
    
    return_value = 0;
    index = 1;
    end = -1;
    if (!args[index])
        show_vars(data);
    while (args[index])
    {
        value = ft_strnstr(args[index], "+=", &end);
        if (value != NULL)
        {
            value = ft_strdup(value);
            name = ft_substr(args[index], 0, end);
        }
        else
        {
            name = get_env_name(args[index]);
            value = get_env_value(args[index]);
        }
        if (name)
        {
            if (*name && is_identifier(name))
            {
                if (ft_strchr(args[index], '=') == NULL)
                {
                    if (!search_var(&(data->env_vars), name))
                        if (!is_unset_var(&(data->unset_vars), name))
                            ft_lstadd_back(&(data->unset_vars), ft_lstnew(ft_strdup(name)));
                }
                else
                {
                    if (is_double_quote_token(value) || is_single_quote_token(value))
                         value = remove_quotes(value);
                    if (is_unset_var(&(data->unset_vars), name))
                        remove_unset_var(&(data->unset_vars), name);
                    if (end != -1)
                        append_env_var(&(data->env_vars), name, value);
                    else
                        change_env_var(&(data->env_vars), name, value);
                }
            }
            else
            {
                return_value = 1;
                ft_putstr_fd("not a valid identifier ", 2);
                ft_putstr_fd(args[index], 1);
                ft_putchar_fd('\n', 1);
            }
            free(name);
        }
        if (value)
            free(value);
        index++;
    }
    return (return_value);
}
