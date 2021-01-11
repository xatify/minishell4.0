/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 09:24:00 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/11 12:26:23 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

bool    is_single_quote_token(char *token)
{
    return ((token[0] == '\'')? TRUE: FALSE);
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
    return ((token[0] == '"')? TRUE: FALSE);
}

void    expand_env_var(t_stack **primary_stack, t_stack **secondary_stack, t_env_vars **vars)
{
       t_token      *var;
       t_env_vars    *env_var;
    
        var = NULL;
       empty_stack(secondary_stack, &var);
       if (var && *(var->tkn))
       {
            env_var = search_var(vars, var->tkn);
            if (env_var)
                push_str_to_stack(primary_stack, env_var->value);
            free_tokens(&var);
       }
}

void    expand_dollar_sign(char **token, t_env_vars *vars, int *exit_status, t_stack **primary_stack)
{
    t_stack *secondary_stack;
    
    secondary_stack = NULL;
    if (**token == '?')
    {
        (*token)++;
        push_str_to_stack(primary_stack, ft_itoa(*exit_status));
        return;
    }
    if (!(is_underscore(**token) || is_alpha(**token)))
        push(&secondary_stack, *(*token)++);
    while (**token)
    {
        if (is_alpha(**token) || is_num(**token) || is_underscore(**token))
        {
            push(&secondary_stack, **token);
            (*token)++;
        }
        else
            break;
    }
    expand_env_var(primary_stack, &secondary_stack, &vars);
}

int     expand_double_quote_token(char **token, t_env_vars * vars, int *exit_status)
{
    char    *tmp;

    tmp = (*token) + 1;
    (*token)[ft_strlen((*token) + 1)] = '\0';
    if (expand_unquoted_token(&tmp, vars, exit_status))
    {
        free(token);
        (*token) = tmp;
        return (1);
    }
    return (0);
}

int     expand_unquoted_token(char **token, t_env_vars *vars, int *exit_status)
{
    t_stack     *stack;
    int         first_back_slash;
    char        *tmp;
    t_token     *tmp_token;
   
    first_back_slash = 0;
    stack = NULL;
    tmp = (*token);
    while (*tmp)
    {
        if (*tmp != '$' && *tmp != '\\')
        {
            if (stack && stack->special)
                pop(&stack);
            push(&stack, *tmp);
        }
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
            if (stack && stack->special)
            {
                pop(&stack);
                push(&stack, *tmp);
            }
            else
            {
                tmp++;
                expand_dollar_sign(&tmp, vars, exit_status, &stack);
            }
        }
        tmp++;
    }
    tmp_token = NULL;
    if (stack)
    {
        empty_stack(&stack, &tmp_token);
        (*token) = ft_strdup(tmp_token->tkn);
    }
    else
    {
       token = NULL;
       return (1);
    }
    if (*token)
        return (1);
    return (0);
}

int    expand_token(char **token, t_env_vars *vars, int *exit_status)
{
    if (is_single_quote_token(*token))
    {
        if (expand_single_quote_token(token))
            return (1);
    }
    else if (is_double_quote_token(*token))
    {
        if (expand_double_quote_token(token, vars, exit_status))
            return (1);
    }
    else if (expand_unquoted_token(token, vars, exit_status))
        return (1);
    return (0);
}

int     expand_list(t_strlist *list, t_env_vars *vars, int *exit_status)
{
    if (!list)
        return (1);
    if (expand_token(&(list->str), vars, exit_status))
    {
        
        return (expand_list(list->next, vars, exit_status));
    }
    else
        return (0);
}

int     expand(t_simple_command *cmd, t_env_vars *vars, int *exit_status)
{
    if ( expand_token(&(cmd->cmd_name), vars, exit_status) && 
        expand_list(cmd->arguments, vars, exit_status) &&
        expand_list(cmd->infiles, vars, exit_status) &&
        expand_list(cmd->outfiles, vars, exit_status) &&
        expand_list(cmd->append_outfiles, vars, exit_status))
        return (1);
    return (0);
}

int    expand_pipeline(t_pipeline *parse_tree, t_env_vars *vars, int *exit_status)
{
    t_simple_command *cmd;

    cmd = parse_tree->simple_cmd;
    while (cmd)
    {
        if (!expand(cmd, vars, exit_status))
            return (0);
        cmd = cmd->next;
    }
    return (1);
}

void    perform_expansions(t_pipeline *parse_tree, t_env_vars *vars, int *exit_status)
{
    if (parse_tree)
    {
        if (expand_pipeline(parse_tree, vars, exit_status))
            perform_expansions(parse_tree->next, vars, exit_status);
    }
}