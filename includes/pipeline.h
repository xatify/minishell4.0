/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 09:50:20 by keddib            #+#    #+#             */
/*   Updated: 2021/01/13 09:51:20 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINE_H
# define PIPELINE_H

/*
** simple command linked list methodes
*/

t_pipeline	*new_pipe_line(void);
void        free_pipeline(t_pipeline *pipeline);
void        free_pipeline_list(t_pipeline *pipeline_head);
t_pipeline	*last_pipeline(t_pipeline *pipeline);
void        add_back_pipeline(t_pipeline **pipe_head, t_pipeline *pipeline);
void		show_pipeline(t_pipeline *pipeline);


#endif
