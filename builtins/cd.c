/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 09:29:16 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/06 09:42:35 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* change corrent directory to path if path is not null otherwise to $HOME */

int     cd(char *path, t_env_vars **vars)
{
    char    *dir;

    dir = (path) ? path: search_var(vars, "HOME")->value;
    return (!chdir(dir));
}