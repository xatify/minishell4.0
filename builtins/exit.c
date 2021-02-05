/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 09:25:50 by abbouzid          #+#    #+#             */
/*   Updated: 2021/02/03 10:54:24 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

BOOL is_arg_alpha(char *s)
{
    int i;

    i = 0;
    while (s[i])
    {
        if (i == 0 && s[i] == '-')
        {
            i++;
            continue;
        }
        if (i > 0 && s[i] == '-')
            return (TRUE);
        if (is_alpha(s[i]))
            return (TRUE);
        i++;
    }
    return (FALSE);
}

int    exit_(t_data *data, char **argv)
{
    int     status;
    int     ex;

    status = 0;
    ex = 0;
    if (argv[1] && argv[2])
    {
        ft_putstr_fd("exit\ntoo many arguments\n", 1);
        return (1);
    }
    if (argv[1])
    {
        status = ft_atoi(argv[1], &ex);
        if (ex == 1 || is_arg_alpha(argv[1]))
        {
            ft_putstr_fd("exit\nnumeric argument required\n", 1);
            status = 255;
        }
    }
    ft_lstclear(&(data->env_vars), free_env_var);
    ft_lstclear(&(data->unset_vars), free_pipeline);
    free(data->input_cmd);
    ft_lstclear(&(data->parse_tree), free_pipeline);
    free(data);
    free_argv(argv);
    exit(status);
}
