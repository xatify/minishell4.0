/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 23:34:09 by abbouzid          #+#    #+#             */
/*   Updated: 2020/12/14 10:01:45 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int 	count_tokens(char *cmd)
{
	int		count;

	count = 0;
	
	while (*cmd)
	{
		while (*cmd == '\t' || *cmd == ' ')
			cmd++;
		if (*cmd)
			count++;
		while (*cmd != '\t' && *cmd != ' ' && *cmd)
			cmd++;
	}
	return (count);
}

static int		token_len(char *cmd)
{
	int		len;

	len = 0;
	while (cmd[len] && cmd[len] != ' ' && cmd[len] != '\t')
		len++;
	return (len);
}

static void	free_tokens(char **tokens)
{
	char	**tmp;

	tmp = tokens;
	while (*tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(tokens);
}


char	**lexer(char *cmd)
{
	char 	**tokens;
	int		count;
	int		index;
	int		len;

	count = count_tokens(cmd);
	if (! (tokens = (char **)malloc((count + 1) * sizeof(char *))))
		return (NULL);
	index = 0;
	while (index < count)
	{
		len = token_len(cmd);
		if (!(tokens[index] = (char *)malloc((len + 1) * sizeof(char))))
		{
			free_tokens(tokens);
			return (NULL);
		}
		ft_strlcpy(tokens[index], cmd, len);
		tokens[index][len] = '\0';
		cmd += len;
		while(*cmd == ' ' || *cmd == '\t')
			cmd++;
		index++;
	}
	tokens[index] = NULL;
	return (tokens);
}

