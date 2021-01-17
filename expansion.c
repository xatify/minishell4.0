/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 09:24:00 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/17 14:57:26 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

bool    is_single_quote_token(char *token)
{
    return ((token[0] == '\'')? TRUE: FALSE);
}

char       *expand_single_quote_token(char **token)
{
    (*token)[ft_strlen(*token) - 1] = '\0';
    return (ft_strdup(*token + 1));
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

char     *expand_double_quote_token(char **token, t_env_vars * vars, int *exit_status)
{
    (*token)[ft_strlen(*token) - 1] = '\0';
    return (expand_unquoted_token(*token + 1, vars, exit_status));
}

char         *expand_unquoted_token(char *token, t_env_vars *vars, int *exit_status)
{
    t_stack     *stack;
    int         first_back_slash;
    t_token     *tmp_token;
   
    first_back_slash = 0;
    stack = NULL;
    while (*token)
    {
        if (*token != '$' && *token != '\\')
        {
            if (stack && stack->special)
                pop(&stack);
            push(&stack, *token);
        }
        else if (*token == '\\' && !first_back_slash)
        {
            first_back_slash = 1;
            push(&stack, *token);
            stack->special = 1;
        }
        else if (*token == '\\' && stack->special)
            stack->special = 0;
        else if (*token == '\\' && !stack->special)
        {
            push(&stack, *token);
            stack->special = 1;
        }
        else if (*token == '$')
        {
            if (stack && stack->special)
            {
                pop(&stack);
                push(&stack, *token);
            }
            else
            {
                token++;
                expand_dollar_sign(&token, vars, exit_status, &stack);
                continue;
            }
        }
        token++;
    }
    tmp_token = NULL;
    if (stack)
    {
        empty_stack(&stack, &tmp_token);
        token = ft_strdup(tmp_token->tkn);
        free_tokens(&tmp_token);
        return (token);
    }
    return (NULL);
}

char    *expand(char **token, t_env_vars *vars, int *exit_status)
{
    if (is_double_quote_token(*token))
        return (expand_double_quote_token(token, vars, exit_status));
    else if (is_single_quote_token(*token))
        return (expand_single_quote_token(token));
    return (expand_unquoted_token(*token, vars, exit_status));
}


void    expand_list(t_strlist *list, t_env_vars *vars, int *exit_status)
{
    char    *tmp;
    if (list)
    {
      tmp = expand(&(list->str), vars, exit_status);
      if (!tmp)
        list->str = ft_strdup("");
      else
        list->str = tmp;
      expand_list(list->next, vars, exit_status); 
    }
}

int     expand_cmd(t_simple_command *cmd, t_env_vars *vars, int *exit_status)
{
    char    *tmp;

    if (!cmd)
        return (1);
    tmp = expand(&(cmd->cmd_name), vars, exit_status);
    if (!tmp)
        return (0);
    free(cmd->cmd_name);
    cmd->cmd_name = tmp;
    expand_list(cmd->arguments, vars, exit_status);
    expand_list(cmd->infiles, vars, exit_status);
    expand_list(cmd->outfiles, vars, exit_status);
    expand_list(cmd->append_outfiles, vars, exit_status);
    return (expand_cmd(cmd->next, vars, exit_status));
}

int     expand_pipeline(t_pipeline *pipline, t_data *data)
{
    return (expand_cmd(pipline->simple_cmd, data->env_vars, &(data->exit_status)));
}