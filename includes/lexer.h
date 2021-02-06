/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:12:08 by keddib            #+#    #+#             */
/*   Updated: 2021/02/06 17:58:01 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

/*
** lexer functions
*/

int			handle_single_quote(t_list **stack, char **input_cmd);
int			special(t_list *stack);
int			handle_double_quote(t_list **stack, char **input_cmd);
int			handle_space(t_list **stack, t_list **tokens, int *error);
t_list		*tokenizer(int error, t_list **tokens, t_list **stack);
int			handle_end_token(t_list **stack, t_list **tokens);
int			handle_metacharacter(t_list **stack, t_list **tokens,
			char **input_cmd);
int			handle_quotes(t_list **stack, char **input_cmd, int *error);
t_list		*lexer(char *input_cmd);
int			handle_meta(t_list **stack, t_list **tokens, char **input_cmd);

#endif
