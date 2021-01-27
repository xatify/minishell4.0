/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 09:25:50 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/27 11:01:23 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    exit_(t_data *data, char **argv)
{
    int     status;

    status = (argv[1])? ft_atoi(argv[1]): 0;
    free_env_var(data->env_vars);
    free(data->input_cmd);
    free_pipeline_list(data->parse_tree);
    free(data);
    free_argv(argv);
    _exit(status);
}
