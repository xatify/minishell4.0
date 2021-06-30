/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 10:43:36 by abbouzid          #+#    #+#             */
/*   Updated: 2021/06/30 17:39:37 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*g_operators[6] = {">", "<", ">>", "<<", "|", ";"};

t_token	*new_token(char **str)
{
	t_token		*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->tkn = (*str);
	return (token);
}

void	del_token_head(t_list **tokens)
{
	t_list		*tmp;

	tmp = (*tokens)->next;
	ft_lstdelone((*tokens), free_token);
	(*tokens) = tmp;
}

int	token_id(char *token)
{
	int		i;

	i = 0;
	while (i < 6)
	{
		if (!(ft_strcmp(g_operators[i], token)))
			return (i);
		i++;
	}
	return (WORD);
}

int	identify_all_tokens(t_list *tokens)
{
	t_token		*token;
	int			next_id;

	while (tokens)
	{
		token = (t_token *)(tokens->content);
		token->id = token_id(token->tkn);
		if (token->id != WORD)
		{
			if (token->id == SEMICOLON  || token->id == PIPE)
			{
				if (!(tokens->next))
					return (1);
				next_id = token_id(((t_token *)((tokens->next)->content))->tkn);
				if (next_id <= 3)
				{
					tokens = tokens->next;
					continue ;
				}
				else if (next_id == SEMICOLON || next_id == PIPE)
					return (0);
			}
			if (!(tokens->next))
				return (0);
			if (token_id(((t_token *)((tokens->next)->content))->tkn) != WORD)
				return (0);
		}
		tokens = tokens->next;
	}
	return (1);
}

void	free_token(void *token)
{
	free(((t_token *)token)->tkn);
	free(token);
}
