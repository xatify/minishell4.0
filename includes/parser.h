/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:18:12 by keddib            #+#    #+#             */
/*   Updated: 2021/01/12 16:18:58 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/*
** parser functions
*/


t_pipeline      *parser(char *input_cmd);
int            	parse_redirection(t_token **tokens, t_simple_command *command, int redirection);
int     		parse_cmd_name(t_token **tokens, t_simple_command *command);
int     		parse_arguments(t_token **tokens, t_simple_command *command);
t_simple_command 	*parse_simple_command(t_token    **tokens);
t_pipeline      	*parse_pipe_line(t_token **tokens);
void			show_parse_tree(t_pipeline *parse_tree);
void			free_parse_tree(t_pipeline *parse_tree);

#endif
