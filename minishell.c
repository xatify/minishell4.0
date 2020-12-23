/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 22:50:20 by abbouzid          #+#    #+#             */
/*   Updated: 2020/12/23 09:34:17 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		main()
{
	t_token				*tokens;
	char				*input_cmd;
	t_token				*tmp;
	
	while (TRUE)
	{
		write(1, &PROMPT, ft_strlen(PROMPT));
		if (get_input(&input_cmd))
		{
			tokens = tokenizing(input_cmd);
			tmp = tokens;
			while(tmp)
			{
				printf("<\t%-20s> : %d\n", tmp->tkn, tmp->id);
				tmp = tmp->next;
			}
		}
	}
	return (0);
}
