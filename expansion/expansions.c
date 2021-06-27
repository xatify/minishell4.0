/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 09:24:00 by abbouzid          #+#    #+#             */
/*   Updated: 2021/06/27 16:06:21 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expand(t_list *list, t_data *data)
{
	t_list			*stack;
	char			**token;
	char			*tkn;

	stack = NULL;
	tkn = (list->content);
	token = &tkn;
	while (**token)
	{
		push(&stack, *(*token)++);
		if (top_stack(&stack) == '\'' || top_stack(&stack) == '\"')
			expand_quotes(&stack, token, data);
		else
			expand_unquoted_token(&stack, token, data);
	}
	return (str_from_stack(&stack));
}

void	expand_list(t_list *list, t_data *data)
{
	t_list		*tokens;
	int			error;
	t_list		*next;
	t_list		*new_list;
	char		*str;

	error = 0;
	tokens = NULL;
	if (list)
	{
		str = expand(list, data);
		tokens = lexer(str, &error);
		free(str);
		new_list = rm_quotes(tokens);
		next = list->next;
		reexpand_list(list, new_list, next);
		list = next;
		expand_list(list, data);
	}
}

int	expand_redirections(t_list *redirections, t_data *data)
{
	t_list			*tokens;
	t_redirection	*redirection;
	int				error;
	t_list			*list;
	char			*tmp;

	if (redirections)
	{
		list = NULL;
		redirection = (t_redirection *)redirections->content;
		ft_lstadd_back(&list, ft_lstnew(ft_strdup(redirection->file)));
		tmp = expand(list, data);
		tokens = lexer(tmp, &error);
		free(tmp);
		if (ft_lstsize(tokens) > 1)
			return (redirection_error(redirection, list, tokens));
		free(redirection->file);
		rmq(((t_token *)(tokens->content))->tkn);
		redirection->file = ft_strdup(((t_token *)(tokens->content))->tkn);
		ft_lstclear(&tokens, free_token);
		ft_lstclear(&list, free);
		return (expand_redirections(redirections->next, data));
	}
	return (1);
}

int	expand_cmd(t_list *cmds, t_data *data)
{
	t_command	*cmd;

	if (cmds)
	{
		cmd = (t_command *)(cmds->content);
		expand_list(cmd->name_and_args, data);
		if (!expand_redirections(cmd->redirections, data))
			return (0);
		set_cmd_name(cmd);
		expand_cmd(cmds->next, data);
	}
	return (1);
}

int	expand_pipeline(t_pipeline *pipline, t_data *data)
{
	return (expand_cmd(pipline->cmds, data));
}
