/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 22:50:20 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/07 14:17:05 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		main()
{
	t_token				*tokens;
	char				*input_cmd;
	t_token				*tmp;
	//t_pipeline			*parse_tree;
	
	while (TRUE)
	{
		write(1, &PROMPT, ft_strlen(PROMPT));
		if (get_input(&input_cmd))
		{
			tokens = lexer(input_cmd);
			if (tokens)
			{
				tmp = tokens;
				while(tmp)
				{
					printf("<\t%-20s> : %d\n", tmp->tkn, tmp->id);
					tmp = tmp->next;
				}
				// parse_tree = parser(&tokens);
				// show_pipeline(parse_tree);
				//free_tokens(&tokens);
				//free_pipeline_list(parse_tree);
			}
			free(input_cmd);
		}
		
	}
	return (0);
}
