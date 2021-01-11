/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 22:50:20 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/11 15:26:21 by abbouzid         ###   ########.fr       */
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
	t_simple_command	*cmd;
	
	
	argc = 0;
	argv = NULL;
	exit_status = 0;
	env_vars = build_env_vars(envp);
	
	while (TRUE)
	{
		write(1, &PROMPT, ft_strlen(PROMPT));
		if ((ret = get_next_line(0, &input_cmd)))
		{
			tokens = lexer(input_cmd);
			
			if (tokens)
			{
				parse_tree = parser(&tokens);
				if (parse_tree)
				{
					cmd = parse_tree->simple_cmd;
					while(cmd)
					{
						if (expand_cmd(cmd, env_vars, &exit_status))
						{
							show_command(cmd);
							cmd = cmd->next;
						}
						else
						{
							ft_printf("error while expanding\n");
							break;
						}
					}
				}
			}
		}
		free(input_cmd);
	}
	return (0);
}
