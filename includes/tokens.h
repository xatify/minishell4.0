/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:07:30 by keddib            #+#    #+#             */
/*   Updated: 2021/02/01 16:23:33 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

/*
** tokens linked list methodes
*/

enum token {OUTPUT, INPUT, APPEND_OUT, PIPE, SEMICOLON, WORD};
void            del_token_head(t_list **tokens);
t_token         *new_token(char **str);
int             token_id(char *token);
int             identify_all_tokens(t_list *tokens);
void			free_token(void *token);

#endif
