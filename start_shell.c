/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 09:28:43 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/12 09:34:39 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_data  *start_shell(int argc, char **argv, char **envp)
{
    t_data  *data;
    
    argc = 0;
    argv = NULL;
    if (!(data = (t_data *)malloc(sizeof(t_data))))
        return (NULL);
    data->exit_status = 0;
    data->env_vars = build_env_vars(envp);
    return (data);   
}
