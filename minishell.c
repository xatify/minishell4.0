/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 22:50:20 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/11 11:40:47 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		main(int	argc, char **argv, char **envp)
{
	t_token				*tokens;
	t_env_vars			*env_vars;
	char				*input_cmd;
	t_pipeline			*parse_tree;
	int					exit_status;
	int ret;
	
	
	argc = 0;
	argv = NULL;
	exit_status = 0;
	env_vars = build_env_vars(envp);
	show_env_vars(env_vars);
	while (TRUE)
	{
		write(1, &PROMPT, ft_strlen(PROMPT));
		if ((ret = get_next_line(0, &input_cmd)))
		{
			
			tokens = lexer(input_cmd);
			
			if (tokens)
			{
				parse_tree = parser(&tokens);
				perform_expansions(parse_tree, env_vars, &exit_status);
				show_pipeline(parse_tree);
				if (tokens)
					free_tokens(&tokens);
				free_pipeline_list(parse_tree);
			}
		}
		free(input_cmd);
	}
	return (0);
}
