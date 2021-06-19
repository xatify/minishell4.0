/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expan_token2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 19:47:37 by keddib            #+#    #+#             */
/*   Updated: 2021/06/19 12:14:59 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

BOOL	is_single_quote_token(char *token)
{
	if (token[0] == '\'')
		return (TRUE);
	return (FALSE);
}

BOOL	is_double_quote_token(char *token)
{
	if (token[0] == '"')
		return (TRUE);
	return (FALSE);
}

void	set_cmd_name(char *name, t_command *cmd)
{
	t_list		*tmp;

	tmp = cmd->name_and_args->next;
	free(name);
	free(cmd->name_and_args);
	cmd->name_and_args = NULL;
	*(&(cmd->name_and_args)) = tmp;
}
