/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 09:50:20 by keddib            #+#    #+#             */
/*   Updated: 2021/02/03 10:56:58 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINE_H
# define PIPELINE_H

/*
** simple command linked list methodes
*/

t_pipeline	*new_pipe_line(void);
void		free_pipeline(void *pipeline);

#endif
