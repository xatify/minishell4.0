/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:12:08 by keddib            #+#    #+#             */
/*   Updated: 2021/06/25 14:35:54 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

/*
** lexer functions
*/

int			handle_space(t_list **stack, t_list **tokens, int *error);
t_list		*tokenizer(int error, t_list **tokens, t_list **stack);
int			handle_end_token(t_list **stack, t_list **tokens);
int			handle_metacharacter(t_list **stack, t_list **tokens,
				char **input_cmd);
int			handle_quotes(t_list **stack, char **input_cmd, int *error, char q);
t_list		*lexer(char *input_cmd, int *err);
int			handle_meta(t_list **stack, t_list **tokens, char **input_cmd);

#endif
