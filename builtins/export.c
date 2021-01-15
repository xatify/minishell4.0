/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:57:13 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/15 12:38:09 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int     export(char   **args, t_data *data)
{
    char    *name;
    char    *value;
    int     index;
    int     return_value;

    return_value = 0;
    index = 1;
    while (args[index])
    {
        name = get_env_name(args[index]);
        value = get_env_value(args[index]);
        if (name)
        {
            if (*name && is_identifier(name))
            {
                if (ft_strchr(args[index], '=') == NULL)
                    add_strlist(&(data->unset_vars), name);
                else
                {
                    if (is_double_quote_token(value) || is_single_quote_token(value))
                        value = remove_quotes(value);
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
