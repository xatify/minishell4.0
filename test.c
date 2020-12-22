/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 10:00:50 by abbouzid          #+#    #+#             */
/*   Updated: 2020/12/22 08:50:18 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>


typedef	struct	s_stack
{
	char				character;
	struct 		s_stack *next;
	
}				t_stack;

char    pop(t_stack **stack_head);
void	push(t_stack **stack_head, char character);
int     stack_len(t_stack **stack_head);
char    top_stack(t_stack **stack_head);
char    *empty_stack(t_stack **stack_head);

int main(void)
{
    char string[10] = "abcdef";
    int     i;
    t_stack *head;
    t_stack *tmp;
    
    i = 0;
    while (string[i])
    {
        push(&head, string[i]);
        printf("%c", top_stack(&head));
        i++;
    }
    printf("\n%s\n", empty_stack(&head));
    // printf("\nstack len = %d\n", stack_len(&head));
    // while (head)
    // {
    // printf("%c\n", head->character);
    // pop(&head);
    // }
    return (0);
}