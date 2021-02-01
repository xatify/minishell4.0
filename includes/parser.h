/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:18:12 by keddib            #+#    #+#             */
/*   Updated: 2021/02/01 16:11:16 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/*
** parser functions
*/


t_list          *parser(char *input_cmd);
int            	parse_redirection(t_list **tokens, t_command *command, int red);
int     		parse_cmd_name(t_token **tokens, t_command *command);
int     		parse_arguments(t_token **tokens, t_command *command);
t_command 	    *parse_simple_command(t_list    **tokens);
t_pipeline      *parse_pipe_line(t_list **tokens);
void			show_parse_tree(t_pipeline *parse_tree);
void			free_parse_tree(t_pipeline *parse_tree);

#endif
