/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 10:28:31 by abbouzid          #+#    #+#             */
/*   Updated: 2021/06/18 12:22:37 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_pipeline	*new_pipe_line(void)
{
	t_pipeline	*pipeline;

	pipeline = (t_pipeline *)malloc(sizeof(t_pipeline));
	if (!pipeline)
		return (NULL);
	ft_memset(pipeline, 0, sizeof(t_pipeline));
	return (pipeline);
}

void	free_pipeline(void *pipeline)
{
	if (!(pipeline))
		return ;
	ft_lstclear(&(((t_pipeline *)pipeline)->cmds), free_command);
	free(pipeline);
	pipeline = NULL;
}
