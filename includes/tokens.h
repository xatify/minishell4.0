/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:07:30 by keddib            #+#    #+#             */
/*   Updated: 2021/01/12 16:10:46 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

/*
** tokens linked list methodes
*/

enum token {OUTPUT, INPUT, APPEND_OUT, PIPE, SEMICOLON, WORD};
void            del_token_head(t_token **tokens);
int             token_id(char *token);
t_token 		*new_token(char **str);
int            identify_all_tokens(t_token *tokens);
t_token 		*last_token(t_token *tokens);
void			add_token(t_token **tokens, t_token *new_token);
void			free_tokens(t_token **head);

#endif
