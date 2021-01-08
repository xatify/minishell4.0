/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 22:50:20 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/08 09:00:54 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		main()
{
	t_token				*tokens;
	char				*input_cmd;
	t_token				*tmp;
	//t_pipeline			*parse_tree;
	int ret;
	while (TRUE)
	{
		write(1, &PROMPT, ft_strlen(PROMPT));
		if ((ret = get_next_line(0, &input_cmd)))
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
