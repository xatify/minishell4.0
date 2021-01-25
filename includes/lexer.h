/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:12:08 by keddib            #+#    #+#             */
/*   Updated: 2021/01/25 08:05:12 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H


/*
** lexer functions
*/

int     handle_single_quote(t_stack **stack, char **input_cmd);
int     special(t_stack *stack);
int     handle_double_quote(t_stack **stack, char **input_cmd);
int     handle_metacharacter(t_stack **stack, t_token **tokens, char **input_cmd);
int      handle_quotes(t_stack **stack, char **input_cmd);
t_token    *lexer(char *input_cmd);

#endif
