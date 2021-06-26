/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 09:24:00 by abbouzid          #+#    #+#             */
/*   Updated: 2021/06/26 18:33:10 by keddib           ###   ########.fr       */
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
		if (new_list)
		{
			ft_lstadd_back(&(new_list), next);
			if (new_list)
			{
				free(list->content);
				list->content = new_list->content;
				list->next = new_list->next;
				free(new_list);
			}
		}
		else
		{
			free(list->content);
			list->content = ft_strdup("");
		}
		list = next;
		expand_list(list, data);
	}
}

int		expand_redirections(t_list *redirections, t_data *data)
{
	t_list			*tokens;
	t_redirection	*redirection;
	int				error;
	t_list			*list;
	char *tmp;

	if (redirections)
	{
		list = NULL;
		redirection = (t_redirection *)redirections->content;
		ft_lstadd_back(&list, ft_lstnew(ft_strdup(redirection->file)));
		tmp = expand(list, data);
		tokens = lexer(tmp, &error);
		free(tmp);
		if (ft_lstsize(tokens) > 1)
		{
			ft_putstr_fd(redirection->file, STDERR);
			ft_putstr_fd(AMB_REDIRECT, STDERR);
			ft_lstclear(&list, free);
			ft_lstclear(&tokens, free_token);
			return (0);
		}
		free(redirection->file);
		rmq(((t_token *)(tokens->content))->tkn);
		redirection->file = ft_strdup(((t_token *)(tokens->content))->tkn);
		ft_lstclear(&tokens, free_token);
		ft_lstclear(&list, free);
		return (expand_redirections(redirections->next, data));
	}
	return (1);
}

int 	expand_cmd(t_list *cmds, t_data *data)
{
	t_command	*cmd;
	char		*name;

	if (cmds)
	{
		cmd = (t_command *)(cmds->content);
		expand_list(cmd->name_and_args, data);
		if (!expand_redirections(cmd->redirections, data))
			return (0);
		if (cmd->name_and_args)
		{
			name = cmd->name_and_args->content;
			if (name[0] == '\0')
				set_cmd_name(name, cmd);
		}
		expand_cmd(cmds->next, data);
	}
	return (1);
}

int		expand_pipeline(t_pipeline *pipline, t_data *data)
{
	return (expand_cmd(pipline->cmds, data));
}
