/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelinelistmethodes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 10:28:31 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/07 11:59:33 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

t_pipeline *new_pipe_line(void)
{
    t_pipeline      *pipeline;

    if (!(pipeline = (t_pipeline *)malloc(sizeof(t_pipeline))))
        return (NULL);
    ft_memset(pipeline, 0, sizeof(t_pipeline));
    return (pipeline);
}


void        free_pipeline(t_pipeline *pipeline)
{
    t_simple_command *tmp;
    
    if (!(pipeline))
        return;
    while (pipeline->simple_cmd)
    {
        tmp = pipeline->simple_cmd;
        pipeline->simple_cmd = tmp->next;
        free_command(tmp);
    }
    free(pipeline);
}

void        free_pipeline_list(t_pipeline *pipeline_head)
{
    t_pipeline  *tmp;
    
    while (pipeline_head)
    {
        tmp = pipeline_head->next;
        free_pipeline(pipeline_head);
        pipeline_head = tmp;
    }
}

t_pipeline      *last_pipeline(t_pipeline *pipeline)
{
    if (!pipeline)
        return (NULL);       
    if (!pipeline->next)
        return (pipeline);
    return (last_pipeline(pipeline->next));
}

void            add_back_pipeline(t_pipeline **pipe_head, t_pipeline *pipeline)
{
    if (!(*pipe_head))
        (*pipe_head) = pipeline;
    else
        last_pipeline((*pipe_head))->next = pipeline;
}

void        show_pipeline(t_pipeline *pipeline)
{
    if (pipeline)
    {
        show_command(pipeline->simple_cmd);
        if (pipeline->next)
            ft_printf(" ; ");
        show_pipeline(pipeline->next);       
    }
}