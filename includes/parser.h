/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:18:12 by keddib            #+#    #+#             */
/*   Updated: 2021/06/25 14:25:26 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/*
** parser functions
*/

t_list			*parser(char *input_cmd, int *err);
int				parse_redirection(t_list **tokens, t_command *command, int red);
int				parse_name_and_args(t_list **tokens, t_command *command);
t_command		*parse_command(t_list **tokens);
t_pipeline		*parse_pipe_line(t_list **tokens);
t_pipeline		*new_pipline(t_list **tokens);

#endif
