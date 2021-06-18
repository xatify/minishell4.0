/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_methodes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 10:00:32 by abbouzid          #+#    #+#             */
/*   Updated: 2021/06/18 08:04:20 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	is_built_in(t_list *name_args)
{
	char	*cmd_name;

	cmd_name = name_args->content;
	if (!ft_strcmp("cd", cmd_name))
		return ('c');
	else if (!ft_strcmp("echo", cmd_name))
		return ('e');
	else if (!ft_strcmp("env", cmd_name))
		return (('n'));
	else if (!ft_strcmp("exit", cmd_name))
		return ('x');
	else if (!ft_strcmp("export", cmd_name))
		return ('p');
	else if (!ft_strcmp("pwd", cmd_name))
		return ('w');
	else if (!ft_strcmp("unset", cmd_name))
		return ('u');
	return ('\0');
}
