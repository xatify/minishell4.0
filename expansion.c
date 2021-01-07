/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 09:24:00 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/07 15:45:36 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

bool    is_single_quote_token(char *token)
{
    if (token[0] == '\'' && token[ft_strlen(token) + 1] == '\0')
        return (TRUE);
    return (FALSE);
}

int     expand_single_quote_token(char **token)
{
    char    *tmp;
    
    (*token)[ft_strlen((*token)) + 1] = '\0';
    tmp = (*token);
    if (((*token) = ft_strdup((*token) + 1)))
    {
        free(tmp);
        return (1);
    }
    return (0);
}

bool    is_double_quote_token(char *token)
{
    if (token[0] == '"' && token[ft_strlen(token) + 1] == '\0')
        return (TRUE);
    return (FALSE);
}

void    expand_dollar_sign(char **token, t_env_vars *vars, int *exit_status)
{
    
}
int     expand_double_quote_token(char **token, t_env_vars * vars, int *exit_status)
{
    char    *tmp;
    t_stack *stack;
    int     first_back_slash;

    first_back_slash = 0;
    tmp = (*token) + 1;
    (*token)[ft_strlen((*token) + 1)] = '\0';
    stack = NULL;
    while (*tmp)
    {
        if (*tmp != '$' && *tmp != '\\')
            push(&stack, *tmp);
        else if (*tmp == '\\' && !first_back_slash)
        {
            first_back_slash = 1;
            push(&stack, *tmp);
            stack->special = 1;
        }
        else if (*tmp == '\\' && stack->special)
            stack->special = 0;
        else if (*tmp == '$')
        {
            if (stack->special)
            {
                pop(stack);
                push(&stack, *tmp);
            }
            else
                expand_dollar_sign(&tmp, vars, exit_status);
        }
    }
}


int    expand_token(char **token, t_env_vars *vars, int *exit_status)
{
    char    *tmp;

    if (is_single_quote_token(*token))
    {
        if (expand_single_quote_token(token))
            return (1);
        return (0);
    }
    else if (is_double_quote_token(*token))
    {
        if (expand_double_quote_token(token, vars, exit_status))
            return (1);
        return (0);
    }
}
void    expand(t_simple_command *cmd, t_env_vars *vars, int *exit_status)
{
    expand_token(&(cmd->cmd_name), vars, exit_status);
    expand_list(cmd->arguments, vars, exit_status);
    expand_list(cmd->infiles, vars, exit_status);
    expand_list(cmd->outfiles, vars, exit_status);
    expand_list(cmd->append_outfiles, vars, exit_status);
}