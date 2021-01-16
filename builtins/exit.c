/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 09:25:50 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/16 10:50:50 by abbouzid         ###   ########.fr       */
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
    exit(status);
}