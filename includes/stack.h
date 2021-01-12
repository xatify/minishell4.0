/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:11:11 by keddib            #+#    #+#             */
/*   Updated: 2021/01/12 16:11:38 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

/*
** stack to handle the double quote strings
*/

char    pop(t_stack **stack_head);
void	push(t_stack **stack_head, char character);
int     stack_len(t_stack **stack_head);
char    top_stack(t_stack **stack_head);
void    free_stack(t_stack **stack);
int		empty_stack(t_stack **stack_head, t_token **tokens);
void	is_metacharacter(t_stack **stack);
void	push_str_to_stack(t_stack **stack, char *str);

#endif
