/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:07:30 by keddib            #+#    #+#             */
/*   Updated: 2021/02/08 17:16:49 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

/*
** tokens linked list methodes
*/

void			del_token_head(t_list **tokens);
t_token			*new_token(char **str);
int				token_id(char *token);
int				identify_all_tokens(t_list *tokens);
void			free_token(void *token);

#endif
