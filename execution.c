/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 09:44:48 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/12 10:26:55 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void    execute_built_in(char built_in, t_data *data, t_simple_command *cmd)
{
    
}

void    execute_simple_cmd(t_data *data, t_simple_command *cmd)
{
    char    built_in;

    built_in = is_build_in(cmd->cmd_name);
    if (built_in != '\0')
        execute_built_in(built_in, data, cmd);
    else
        execute_binary(data, cmd);
}

int     execute(t_data   *data)
{
        
}

