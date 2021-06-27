/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecrions_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 17:14:09 by keddib            #+#    #+#             */
/*   Updated: 2021/06/27 17:15:17 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_redirection	*new_redirection(char *file, int type, t_command *command)
{
	t_redirection	*redirection;

	redirection = (t_redirection *)malloc(sizeof(t_redirection));
	if (!redirection)
		return (NULL);
	if (type == HEREDOC)
		set_herdoc(file, redirection, command);
	else
	{
		redirection->file = ft_strdup(file);
		redirection->type = type;
	}
	return (redirection);
}

void	free_redirections(void *redirection)
{
	if (!redirection)
		return ;
	free(((t_redirection *)redirection)->file);
	free(redirection);
}

void	free_tmp_files(void *tmp_file)
{
	unlink(tmp_file);
	free(tmp_file);
}
