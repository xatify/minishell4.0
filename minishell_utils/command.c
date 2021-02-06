/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 10:17:15 by abbouzid          #+#    #+#             */
/*   Updated: 2021/02/05 17:47:48 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_command		*new_cmd(void)
{
	t_command	*cmd;

	if (!(cmd = (t_command *)malloc(sizeof(t_command))))
		return (NULL);
	ft_memset(cmd, 0, sizeof(t_command));
	return (cmd);
}

void			free_command(void *cmd)
{
	t_command	*command;

	if (!cmd)
		return;
	command = (t_command *)cmd;
	ft_lstclear(&(command->name_and_args), free);
	ft_lstclear(&(command->redirections), free_redirections);
	free(command);
}
