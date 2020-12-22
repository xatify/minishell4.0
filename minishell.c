/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 22:50:20 by abbouzid          #+#    #+#             */
/*   Updated: 2020/12/22 10:44:49 by abbouzid         ###   ########.fr       */
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
				ft_printf("<%s>\n", tmp->tkn);
				tmp = tmp->next;
			}
		}
	}
	return (0);
}
